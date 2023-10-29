//
// Created by guru on 11.10.23.
//

#ifndef DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
#define DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H

#include "DPF/distrho/DistrhoDetails.hpp"
#include "DPF/distrho/extra/RingBuffer.hpp"
#include "Settings.h"
#include "joystick-gateway.h"
#include <algorithm>
#include <linux/joystick.h>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace DoJoyStick {
    class MidiObserver {
    public:
        virtual void sendMidiEvent(const MidiEvent &midiEvent) = 0;
    };

    class JoystickMidiMediator {
    public:
        explicit JoystickMidiMediator(const Settings &settings);
        void run_main_loop();
        virtual ~JoystickMidiMediator();

        void addObserver(MidiObserver *const observer) { observers.push_back(observer); };
        void removeObserver(MidiObserver *const observer) {
            auto predicate = [&observer](const MidiObserver *elem) { return elem == observer; };
            observers.erase(std::remove_if(observers.begin(), observers.end(), predicate), observers.end());
        };

        void notifyObservers(const MidiEvent &midiEvent) {
            for (auto observer: observers) {
                observer->sendMidiEvent(midiEvent);
            }
        }

    private:
        static void
        event_handler(JoystickEvent event, void *);
        void setupJoystick();
        //        JoystickGateway joystickGateway;
        //        std::thread joystickThread;

        std::vector<MidiObserver *> observers;
        void sendMidiMessage(const char *msg, size_t size);
        static void printMidiMessage(const char *msg, size_t size, bool hex = true);
    };
}// namespace DoJoyStick
#endif//DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
