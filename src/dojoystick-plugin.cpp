//
// Created by humer on 22/10/2023.
//


#include "DistrhoPlugin.hpp"
#include "JoystickMidiMediator.h"
#include <thread>

START_NAMESPACE_DISTRHO

class DoJoystickPlugin : public Plugin {
private:
    JoystickMidiMediator *joystickMidiMediator;
    HeapRingBuffer heapRingBuffer;

public:
    DoJoystickPlugin() : Plugin(kParameterCount, 0, 0), gain(1.0) {
        // or RingBufferControl<HeapBuffer> class for more control

        // construction, only needed for heap buffers
        heapRingBuffer.createBuffer(8192);

        joystickMidiMediator = new JoystickMidiMediator("/dev/input/js0", &heapRingBuffer);


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
    const char *getLabel() const override { return "DoJoystick"; }

    const char *getDescription() const override {
        return "Simple amp plugin.";
    }

    const char *getMaker() const override { return "DoJoy"; }

    const char *getLicense() const override { return "AGPL3"; }

    uint32_t getVersion() const override { return d_version(1, 0, 0); }

    int64_t getUniqueId() const override {
        return d_cconst('D', 'o', 'J', 'T');
    }


    void initParameter(uint32_t index, Parameter &parameter) override {
        switch (index) {
            case kGain:
                parameter.name = "Gain";
                parameter.symbol = "gain";
                parameter.ranges.def = 1.0f;
                parameter.ranges.min = 0.0f;
                parameter.ranges.max = 2.0f;
                break;
            default:
                break;
        }
    }

    float getParameterValue(uint32_t index) const override {
        switch (index) {
            case kGain:
                return gain;
            default:
                return 0.0;
        }
    }

    void setParameterValue(uint32_t index, float value) override {
        switch (index) {
            case kGain:
                gain = value;
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
    float gain;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DoJoystickPlugin);
};

Plugin *createPlugin() { return new DoJoystickPlugin(); }

END_NAMESPACE_DISTRHO