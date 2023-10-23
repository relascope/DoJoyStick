//
// Created by humer on 22/10/2023.
//


#include "DistrhoPlugin.hpp"
#include "JoystickMidiMediator.h"

START_NAMESPACE_DISTRHO

    class DoJoystickPlugin : public Plugin {
    public:
        DoJoystickPlugin() : Plugin(kParameterCount, 0, 0), gain(1.0) {
//            JoystickMidiMediator joystick_midi("/dev/input/js0");
//            joystick_midi.run_main_loop();
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

        void run(const float**, float** outputs, uint32_t frames) override
        {
            MidiEvent event;
            //writeMidiEvent(midiEvents[i]);
        }


    private:
        float gain;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DoJoystickPlugin);
    };

    Plugin *createPlugin() { return new DoJoystickPlugin(); }

END_NAMESPACE_DISTRHO