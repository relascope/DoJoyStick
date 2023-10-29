//
// Created by guru on 29.10.23.
//

#ifndef DOJOYSTICK_SRC_DOJOYSTICK_PLUGIN_CPP_DOJOYSTICK_PLUGIN_H_
#define DOJOYSTICK_SRC_DOJOYSTICK_PLUGIN_CPP_DOJOYSTICK_PLUGIN_H_

#include "DistrhoPlugin.hpp"
#include "JoystickMidiMediator.h"
#include "Settings.h"
#include <thread>
// parameter button -> noteOn, noteOff, autoNoteOff, MIDI CC noteNumber, velocity
constexpr uint8_t kMaxButtonNumber = 0xFFU;
class DoJoystickPlugin : public Plugin {
public:
    enum class Parameters {
        kVelocity = 0,
        kParameterCount = 1,
    };

    [[nodiscard]] const DoJoyStick::Settings &getSettings() const {
        return settings;
    }

private:
    std::unique_ptr<DoJoyStick::JoystickMidiMediator> joystickMidiMediator;
    HeapRingBuffer heapRingBuffer;

public:
    DoJoystickPlugin() : Plugin(static_cast<uint32_t>(Parameters::kParameterCount), 0, 0) {
        settings.velocity = 111;
        settings.joyStickDeviceName = "/dev/input/js0";
        heapRingBuffer.createBuffer(8192);

        joystickMidiMediator = std::make_unique<DoJoyStick::JoystickMidiMediator>(settings, &heapRingBuffer);


        //            joystick_midi.run_main_loop();

        // definition

        //            // writing data
        //            myHeapBuffer.writeUInt(size);
        //            myHeapBuffer.writeCustomData(someOtherData, size);
        //            myHeapBuffer.commitWrite();
        //
        //            // reading data
        //            if (myHeapBuffer.isDataAvailableForReading())
        //            {
        //                uint32_t size;
        //                if (myHeapBuffer.readUInt(size) && readCustomData(&anotherData, size))
        //                {
        //                    // do something with "anotherData"
        //                }
        //            }
    }

protected:
    [[nodiscard]] const char *getLabel() const override { return "DoJoyStick"; }

    [[nodiscard]] const char *getDescription() const override {
        return "Joystick to DoJoy music. UseCase: MidiController (e.g. versatile foot drum)";
    }

    [[nodiscard]] const char *getMaker() const override { return "DoJoy.at"; }

    [[nodiscard]] const char *getLicense() const override { return "AGPL3"; }

    [[nodiscard]] uint32_t getVersion() const override { return d_version(1, 0, 1); }

    [[nodiscard]] int64_t getUniqueId() const override {
        return d_cconst('D', 'J', 'o', 'y');
    }


    void initParameter(uint32_t index, Parameter &parameter) override {
        switch (static_cast<Parameters>(index)) {
            case Parameters::kVelocity:
                parameter.name = "velocity";
                parameter.symbol = "gain";// TODO
                parameter.hints |= kParameterIsInteger;
                parameter.ranges.def = 108;
                parameter.ranges.min = 0;
                parameter.ranges.max = 127;
                break;
            default:
                break;
        }
    }

    virtual float getParameterValue(uint32_t index) const override {
        switch (static_cast<Parameters>(index)) {
            case Parameters::kVelocity:
                return settings.velocity;
            default:
                return 0;
        }
    }

    virtual void setParameterValue(uint32_t index, float value) override {
        switch (static_cast<Parameters>(index)) {
            case Parameters::kVelocity:
                settings.velocity = static_cast<uint8_t>(value);
                break;
            default:
                break;
        }
    }


    void run(const float **inputs, float **outputs, uint32_t frames) override {

        if (!heapRingBuffer.isDataAvailableForReading())
            return;

        for (size_t frame_idx = 0; frame_idx < frames && heapRingBuffer.isDataAvailableForReading(); ++frame_idx) {
            MidiEvent midiEvent;
            if (!heapRingBuffer.readCustomType(midiEvent))
                continue;

            midiEvent.frame = frame_idx;

            writeMidiEvent(midiEvent);
        }
    }

private:
    DoJoyStick::Settings settings;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DoJoystickPlugin);
};
#endif//DOJOYSTICK_SRC_DOJOYSTICK_PLUGIN_CPP_DOJOYSTICK_PLUGIN_H_
