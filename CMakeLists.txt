cmake_minimum_required(VERSION 3.7)
project(DoJoystick)

set (CMAKE_CXX_STANDARD 17)

set ( CMAKE_SOURCE_DIR "./" )
file(GLOB TARGET_H "${CMAKE_SOURCE_DIR}/*.h")
file(GLOB TARGET_CPP "${CMAKE_SOURCE_DIR}/*.cpp")
file(GLOB  MIDI_JOYSTICK_SRC glue.c joystick.c midijack.c)
file(GLOB SUB_JOYSTICK_SRC "./MidiJoystick" )
file(GLOB SUB_TARGET_H "${SUB_JOYSTICK_SRC}/*.h")
file(GLOB SUB_TARGET_CPP "${SUB_JOYSTICK_SRC}/*.c")
set(TARGET_SRC ${TARGET_CPP} ${TARGET_H} ${SUB_TARGET_CPP} ${SUB_TARGET_H})
include_directories(${SUB_JOYSTICK_SRC})


add_subdirectory(DPF)

dpf_add_plugin(DoJoystick
        TARGETS jack clap lv2 vst2 vst3
        #  UI_TYPE opengl
        FILES_DSP
        src/dojoystick-plugin.cpp ${TARGET_SRC}
        #  FILES_UI
        #      src/dojoystick-ui.cpp
)

target_include_directories(DoJoystick PUBLIC . src)
