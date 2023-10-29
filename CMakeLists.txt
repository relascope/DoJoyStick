cmake_minimum_required(VERSION 3.7)
project(DoJoyStick)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SOURCE_DIR "./")
file(GLOB TARGET_H "${CMAKE_SOURCE_DIR}/*.h")
file(GLOB TARGET_CPP "${CMAKE_SOURCE_DIR}/*.cpp")
file(GLOB MIDI_JOYSTICK_SRC glue.c joystick.c midijack.c)
file(GLOB SUB_JOYSTICK_SRC "./MidiJoystick")
file(GLOB SUB_TARGET_H "${SUB_JOYSTICK_SRC}/*.h")
file(GLOB SUB_TARGET_CPP "${SUB_JOYSTICK_SRC}/*.c")
set(TARGET_SRC ${TARGET_CPP} ${TARGET_H} ${SUB_TARGET_CPP} ${SUB_TARGET_H})
include_directories(${SUB_JOYSTICK_SRC})

add_subdirectory(DPF)

dpf_add_plugin(DoJoyStick
        TARGETS jack clap lv2 vst2 vst3
        FILES_DSP
        src/dojoystick-plugin.cpp ${TARGET_SRC}
)

target_include_directories(DoJoyStick PUBLIC . src)


Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/exampletest.cpp
        tests/dojoystick-plugin-test.cpp ${TARGET_SRC})

target_include_directories(tests PUBLIC . src ./DPF/distrho)


target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)