class THSDriver2 {
    bool check_checksum(uint16_t data, uint8_t checksum);
public:
    struct measurement {
        float temperature;
        float humidity;
    };

    /*enum class Mode {
        NormalPower,
        LowPower
    };
    enum class Protocol {
        NoClockStretching,
        ClockStretching
    };*/

    bool isConnected();
    optional<measurement> takeMeasurement();
};

extern THSDriver2 THS;