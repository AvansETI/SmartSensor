//
// Created by paulh on 5/7/2020.
//

#ifndef BOARD_SUPPORT_STATEMACHINETESTS_H
#define BOARD_SUPPORT_STATEMACHINETESTS_H

#include <unity.h>
#include <fakeit.hpp>

#include <board-support/state/StateMachine.h>
#include <board-support/state/State.h>

using namespace fakeit;


namespace test_state_StateMachineTests {

    Mock<IState> create_mocked_state() {
        Mock<IState> mock;
        When(Method(mock, init)).AlwaysReturn();
        When(Method(mock, update)).AlwaysReturn();
        When(Method(mock, destroy)).AlwaysReturn();

        return mock;
    }

    void test_StateMachine_add_state() {
        StateMachine* machine = new StateMachine();
        int index = 0;
        Mock<IState> state_mock = create_mocked_state();

        bool success = machine->add_state(&state_mock.get(), index);
        TEST_ASSERT_TRUE(success);
        TEST_ASSERT_NOT_NULL(machine->get_state_on_index(index))
        TEST_ASSERT_TRUE(&state_mock.get() == machine->get_state_on_index(index));
    }

    void test_StateMachine_set_start() {
        StateMachine* machine = new StateMachine();
        int s_index = 0;

        Mock<IState> start_state = create_mocked_state();
        Mock<IState> end_state = create_mocked_state();
        bool success = false;
        success = machine->add_state(&start_state.get(), 0);
        TEST_ASSERT_TRUE(success);

        success = machine->add_state(&end_state.get(), 1);
        TEST_ASSERT_TRUE(success);

        success = machine->set_state(s_index);
        TEST_ASSERT_TRUE(success);
        TEST_ASSERT_NOT_NULL(machine->get_current_state());
        TEST_ASSERT_TRUE(&start_state.get() == machine->get_state_on_index(s_index));
    }

    void test_StateMachine_go_next() {
        StateMachine* machine = new StateMachine();

        Mock<IState> previous_state_mock = create_mocked_state();
        Mock<IState> current_state_mock = create_mocked_state();

        // Adding the states
        machine->add_state(&previous_state_mock.get(), 0);
        machine->add_state(&current_state_mock.get(), 1);

        machine->set_state(0);
        // StateMachine should go next to state
        TEST_ASSERT_TRUE(&previous_state_mock.get() == machine->get_state_on_index(0));
        machine->set_state(1);
        TEST_ASSERT_TRUE(&current_state_mock.get() == machine->get_state_on_index(1));
    }

    void test_StateMachine_go_prev() {
        StateMachine* machine = new StateMachine();

        Mock<IState> previous_state_mock = create_mocked_state();
        Mock<IState> current_state_mock = create_mocked_state();

        // Adding the states
        machine->add_state(&previous_state_mock.get(), 0);
        machine->add_state(&current_state_mock.get(), 1);

        machine->set_state(1);
        // StateMachine should go next to state
        TEST_ASSERT_TRUE(&current_state_mock.get() == machine->get_state_on_index(1));
        machine->revert_state();
        TEST_ASSERT_TRUE(&previous_state_mock.get() == machine->get_state_on_index(0));
    }


    void test_StateMachine_run_start_state() {
        StateMachine* machine = new StateMachine();

        Mock<IState> previous_state_mock = create_mocked_state();
        Mock<IState> current_state_mock = create_mocked_state();

        // Adding the states
        machine->add_state(&previous_state_mock.get(), 0);
        machine->add_state(&current_state_mock.get(), 1);

        machine->set_state(0);
        machine->update();

        Verify(Method(previous_state_mock, init)).Once();
        Verify(Method(previous_state_mock, update)).Once();
    }


    void run() {
        RUN_TEST(test_StateMachine_add_state);
        RUN_TEST(test_StateMachine_set_start);
        RUN_TEST(test_StateMachine_go_next);
        RUN_TEST(test_StateMachine_go_prev);
        RUN_TEST(test_StateMachine_run_start_state);
    }
}

#endif //BOARD_SUPPORT_STATEMACHINETESTS_H
