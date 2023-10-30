//
// Created by guru on 29.10.23.
//
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <thread>

#include "JoystickMidiMediator.h"
using namespace DoJoyStick;

TEST_CASE("Create and destroy MidiMediator", "[JoystickMidiMediator]") {
    {
        Settings sett;
        sett.joyStickDeviceName = "/dev/input/js0";
        auto jm = JoystickMidiMediator(sett);
    }
}

TEST_CASE("Create, RUN and destroy MidiMediator", "[JoystickMidiMediator]") {
    using namespace DoJoyStick;
    {
        Settings sett;
        sett.joyStickDeviceName = "/dev/input/js0";
        auto jm = JoystickMidiMediator(sett);
        jm.startThread();

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

bool called = false;
class TestObserver : public MidiObserver {
public:
    void onMidiEvent(const MidiEvent &midiEvent) override {
        called = true;
    }
};

TEST_CASE("MidiMediator events", "[JoystickMidiMediator]") {
    using namespace DoJoyStick;
    {
        Settings sett;
        sett.joyStickDeviceName = "/dev/input/js0";
        auto jm = JoystickMidiMediator(sett);
        MidiObserver *testObserver = new TestObserver();
        jm.addObserver(testObserver);
        jm.startThread();

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        REQUIRE(called == true);

        delete testObserver;
    }
}