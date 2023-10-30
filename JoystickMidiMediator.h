//
// Created by guru on 11.10.23.
//

#ifndef DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
#define DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H

#include "DPF/distrho/DistrhoDetails.hpp"
#include "DPF/distrho/extra/RingBuffer.hpp"
#include "DPF/distrho/extra/Thread.hpp"
#include "Settings.h"
#include "joystick-gateway.h"
#include <algorithm>
#include <iostream>
#include <linux/joystick.h>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace DoJoyStick {

    class DoJoyStickThread : public DISTRHO::Thread {
    };


    class MidiObserver {
    public:
        virtual void onMidiEvent(const MidiEvent &midiEvent) = 0;
    };
    //
    //    class ThreadProvider {
    //    public:
    //        virtual void startThread(std::function<void(void)>) = 0;
    //        virtual void stopThread();
    //    };

    /** JoyStickMidiMediator
     * is the connection from the joystick to midi
     * to use, you have to provide the Settings and a
     * possibility to run a thread on the desired function.
     * The request for a ThreadProvider (over using std::thread)
     * was made because DISTRHO DPF Plugin framework
     * somehow hast problems, when lv2 manifests are created.
     */
    class JoystickMidiMediator : public DISTRHO::Thread {
    public:
        explicit JoystickMidiMediator(const Settings &settings);
        ~JoystickMidiMediator() override;

        void addObserver(MidiObserver *const observer) {
            std::cout << "observer added...\n"
                      << std::flush;
            observers.push_back(observer);
            std::cout << "obserers size: " << observers.size() << "\n"
                      << std::flush;
        };
        void removeObserver(MidiObserver *const observer) {
            std::cout << "observer removed \n"
                      << std::flush;
            auto predicate = [&observer](const MidiObserver *elem) { return elem == observer; };
            observers.erase(std::remove_if(observers.begin(), observers.end(), predicate), observers.end());
        };

    protected:
        // from DISTRHO::Thread
        void run() override {
            joystickGateway.js_event_loop();
        }

        void notifyObservers(const MidiEvent &midiEvent) {
            std::cout << "NOTIFY... " << observers.size() << "\n"
                      << std::flush;
            for (auto observer: observers) {
                observer->onMidiEvent(midiEvent);
            }
        }

    private:
        static void
        event_handler(JoystickEvent event, void *);
        void setupJoystick();
        JoystickGateway joystickGateway;
        std::thread joystickThread;

        std::vector<MidiObserver *> observers;
        void sendMidiMessage(const char *msg, size_t size);
        static void printMidiMessage(const char *msg, size_t size, bool hex = true);
    };
}// namespace DoJoyStick
#endif//DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
