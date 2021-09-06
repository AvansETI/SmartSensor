#pragma once

#include <stdint.h>
#include <assert.h>
#include <util/delay.h>
#include <boardsupport.h>
#include <avr/interrupt.h>
#include <board-support/util/SerialLogger.h>

enum class future_status {
    ready,
    timeout,
    deferred
};

template<typename T>
class optional {
    bool has_value;
    T t;

    public:
    optional() : has_value(false) {};
    optional(const T& t) : has_value(true), t(t) {}

    optional<T>& operator= (const T& t) {has_value = true; this->t = t; return *this; }

    const T& operator*() { assert(has_value); return t; }
    operator bool() {return has_value;}

    const T& value() { assert(has_value); return t;}

    void reset() {has_value = false;}
};

namespace details {
    union TWIControlRegister {
        uint8_t raw;
        struct {
            uint8_t interupt_enable:1;
            uint8_t z_reserved:1;
            uint8_t twi_enable:1;
            uint8_t write_collision_flag:1;
            uint8_t STOP_condition:1;
            uint8_t START_condition:1;
            uint8_t enable_acknowledge:1;
            uint8_t interrupt_flag:1;
        } bits;
        static_assert(sizeof(bits) == 1, "there should be 8 bits, and they should therefore be representable by a single byte");

        TWIControlRegister() : raw(0) {}
        TWIControlRegister(uint8_t value) : raw(value) {}
        TWIControlRegister& operator =(uint8_t value) {raw = value; return *this;}
        operator uint8_t() { return raw; }
    };

    template<typename T> auto& get_future_frame(T& t) {
        return t.m_frame;
    }

    template<typename T> auto& get_data_register(T& t) {
        return t.DataRegister();
    }

    template<typename T> auto& get_control_register(T& t) {
        return t.ControlRegister();
    }

    template<typename T> uint8_t get_status(T& t) {
        return t.extractStatusCode();
    }

    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template<class T, T v>
    struct integral_constant {
        static constexpr T value = v;
        using value_type = T;
        using type = integral_constant; // using injected-class-name
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; } //since c++14
    };

    template<class T, class U>
        struct is_same : integral_constant<bool, false> {};
        
        template<class T>
        struct is_same<T, T> : integral_constant<bool, true> {};

        struct future_frame {
        volatile uint8_t m_value;
        volatile uint8_t m_expected_result_code;
        volatile uint8_t m_status_code;
        enum class State {
            NoValue,
            Value,
            ValueGiven
        } volatile m_state = State::ValueGiven;
    };
}

template <typename T>
class future final {
    template <uintptr_t _StatusRegister, uintptr_t _BitRateRegister, uintptr_t _PeripheralAdressRegister, uintptr_t _DataRegister, uintptr_t _ControlRegister>
    friend class TWIDriver2;

    details::future_frame* const m_frame;
    future() = delete;
    future(details::future_frame *const frame) : m_frame(frame) {}

    template <typename Type = T>
    typename details::enable_if<details::is_same<Type, void>::value, bool>::type get_impl() {
        //if (m_frame->m_status_code != m_frame->m_expected_result_code) SerialLogger0.printf("\tstatus_code := %x, expected_result_code := %x\n", m_frame->m_status_code, m_frame->m_expected_result_code);
        return m_frame->m_status_code == m_frame->m_expected_result_code;
    }

    template <typename Type = T>
    typename details::enable_if<!details::is_same<Type, void>::value, optional<Type>>::type get_impl() {
        //if (m_frame->m_status_code != m_frame->m_expected_result_code) SerialLogger0.printf("\tstatus_code := %x, expected_result_code := %x\n", m_frame->m_status_code, m_frame->m_expected_result_code);
        return (m_frame->m_status_code == m_frame->m_expected_result_code) ? optional<uint8_t>(static_cast<uint8_t>(m_frame->m_value)) : optional<uint8_t>();
    }
    public:
    ~future() { if (m_frame->m_state == details::future_frame::State::NoValue) SerialLogger0.print("destructing future while task has not completed\n"); }

    future(const future&) = delete;
    future(future&&) = default;

    future& operator=(const future&) = delete;
    future& operator=(future&&) = default;

    auto get() { using namespace details; if(m_frame->m_state != future_frame::State::Value) SerialLogger0.print("invalid get\n"); assert(m_frame->m_state == future_frame::State::Value); m_frame->m_state = future_frame::State::ValueGiven; return get_impl(); }
    bool valid() { using namespace details; return m_frame->m_state != future_frame::State::ValueGiven; }
    future<T>& wait() { using namespace details; assert(m_frame->m_state != future_frame::State::ValueGiven); while (m_frame->m_state != future_frame::State::Value); return *this; }
    future_status wait_for_ms(double ms) = delete; // @TODO add impl
    future_status wait_for_us(double us) = delete; // @TODO add impl
    future_status wait_until() = delete; 
}; 

enum class TWIMode {
        Indeterminate,
        MasterTransmitter,
        MasterReciever,
        // @TODO implement support for these modes
        //PeripheralTransmitter,
        //PeripheralReciever
    };

template <uintptr_t _StatusRegister, uintptr_t _BitRateRegister, uintptr_t _PeripheralAdressRegister, uintptr_t _DataRegister, uintptr_t _ControlRegister>
class TWIDriver2 {
    template<typename T> friend auto& details::get_future_frame(T& t);
    template<typename T> friend auto& details::get_data_register(T& t);
    template<typename T> friend auto& details::get_control_register(T& t);
    template<typename T> friend uint8_t details::get_status(T& t);

    inline auto& StatusRegister() { return _SFR_MEM8(_StatusRegister); }
    inline auto& BitRateRegister() { return _SFR_MEM8(_BitRateRegister); }
    inline auto& PeripheralAdressRegister() { return _SFR_MEM8(_PeripheralAdressRegister); }
    inline auto& DataRegister() { return _SFR_MEM8(_DataRegister); }
    inline auto& ControlRegister() { return _SFR_MEM8(_ControlRegister); }

    details::future_frame m_frame;

    uint8_t m_status_code = 0;

    TWIMode m_mode = TWIMode::Indeterminate;
    bool m_in_transmission = false;

    // @TODO implement b
    //bool twi_enabled;
    //bool outstanding_future;
    
    TWIDriver2(const TWIDriver2&) = delete;
    TWIDriver2& operator=(const TWIDriver2&) = delete;

    inline auto extractStatusCode() {
        return m_status_code = _SFR_MEM8(_StatusRegister) & 0b1111'1000;
    }

    future<void> generic_start(const uint8_t expected_result, const TWIMode mode) {
        using namespace details;

        assert(m_frame.m_state == future_frame::State::ValueGiven);
        assert(mode == TWIMode::MasterReciever || mode == TWIMode::MasterTransmitter);

        m_mode = mode;
        m_in_transmission = true;

        m_frame.m_expected_result_code = expected_result;
        m_frame.m_state = future_frame::State::NoValue;

        TWIControlRegister cr{0};
        cr.bits.twi_enable = 1;
        cr.bits.START_condition = 1;
        cr.bits.interrupt_flag = 1;
        cr.bits.interupt_enable = 1;
        ControlRegister() = cr;
        return future<void>(&m_frame);
    }

    future<uint8_t> generic_read(const bool acknowledge) {
        using namespace details;

        assert(m_mode == TWIMode::MasterReciever);

        m_frame.m_expected_result_code = acknowledge ? 0x50 : 0x58;
        m_frame.m_state = future_frame::State::NoValue;

        TWIControlRegister cr{0};
        cr.bits.twi_enable = 1;
        cr.bits.enable_acknowledge = acknowledge;
        cr.bits.interrupt_flag = 1;
        cr.bits.interupt_enable = 1;
        ControlRegister() = cr;

        return future<uint8_t>(&m_frame);  
    }
public:
    TWIDriver2() = default;

    void setBitrate(uint32_t bitrate) {
        using namespace details;
        // @TODO esnure bitrate is valid, and set prescaler when needed
        StatusRegister() = 0b00; // set prescaler (lower two bits of the status register) {00 = 1, 01 = 4, 10 = 16, 11 = 64}
        BitRateRegister() = ((F_CPU/bitrate)-16)/2; // set the bitrate, calculation derived from the ATmega324PB datasheet pg. 257
        extractStatusCode();
    }

    void enable() {
        using namespace details;

        if(TWIControlRegister(ControlRegister()).bits.twi_enable) 
            SerialLogger0.print("calling TWIDriver::enable() even though the TWI was already enabled\n");

        m_in_transmission = false;
        m_mode = TWIMode::Indeterminate;
        TWIControlRegister cr{0};
        cr.bits.twi_enable = 1;
        ControlRegister() = cr;
    }

    void disable() {
        using namespace details;

        if(!TWIControlRegister(ControlRegister()).bits.twi_enable) 
            SerialLogger0.print("calling TWIDriver::disable() even though the TWI was already disabled\n");

        m_in_transmission = false;
        m_mode = TWIMode::Indeterminate;
        ControlRegister() = 0;
    }

    inline future<void> start(const TWIMode mode) {
        assert(m_in_transmission == false);
        return generic_start(0x08, mode);
    }

    inline future<void> repeated_start(const TWIMode mode) {
        assert(m_in_transmission);
        return generic_start(0x10, mode);
    }

    void stop() {
        using namespace details;

        TWIControlRegister cr{0};
        cr.bits.twi_enable = 1;
        cr.bits.STOP_condition = 1;
        cr.bits.interrupt_flag = 1;
        ControlRegister() = cr;  
        while (TWIControlRegister(ControlRegister()).bits.STOP_condition);
        m_in_transmission = false;
        m_mode = TWIMode::Indeterminate;
    }

    future<void> select(const uint8_t adress) {
        using namespace details;

        assert(m_mode == TWIMode::MasterReciever || m_mode == TWIMode::MasterTransmitter);

        m_frame.m_expected_result_code = (m_mode == TWIMode::MasterTransmitter) ? 0x18 : 0x40;
        m_frame.m_state = future_frame::State::NoValue;

        TWIControlRegister cr{0};
        DataRegister() = adress | (m_mode == TWIMode::MasterReciever);
        cr.bits.twi_enable = 1;
        cr.bits.interrupt_flag = 1;
        cr.bits.interupt_enable = 1;
        ControlRegister() = cr;

        return future<void>(&m_frame);
    }

    future<void> write(const uint8_t data) {
        using namespace details;

        assert(m_mode == TWIMode::MasterTransmitter);

        m_frame.m_expected_result_code = 0x28;
        m_frame.m_state = future_frame::State::NoValue;

        TWIControlRegister cr{0};
        DataRegister() = data;
        cr.bits.twi_enable = 1;
        cr.bits.interrupt_flag = 1;
        cr.bits.interupt_enable = 1;
        ControlRegister() = cr;  
        return future<void>(&m_frame);
    }

    inline future<uint8_t> read_ack() {
        return generic_read(true);
    }

    inline future<uint8_t> read_nack() {
        return generic_read(false);
    }
};

#if TWI0_ENABLED
extern TWIDriver2<0xB9, 0xB8, 0xBA, 0xBB, 0xBC> TWI2_0;
#endif

#if TWI1_ENABLED
extern TWIDriver2<0xD9, 0xD8, 0xDA, 0xDB, 0xDC> TWI2_1;
#endif