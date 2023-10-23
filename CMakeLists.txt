cmake_minimum_required(VERSION 3.7)
project(DoJoystick)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(DPF)

dpf_add_plugin(DoJoystick
        TARGETS jack clap lv2 vst2 vst3
        #  UI_TYPE opengl
        FILES_DSP
        src/dojoystick-plugin.cpp
        #  FILES_UI
        #      src/dojoystick-ui.cpp
)

target_include_directories(DoJoystick PUBLIC . src)
