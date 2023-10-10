cmake_minimum_required(VERSION 3.26)
project(DoJoystick)

set(CMAKE_CXX_STANDARD 20)


###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
#file(GLOB_RECURSE sources      *.cpp *.h *.hpp *.c) !!! GLOB_RECURSE also finds data in cmake-* folders
SET ( CMAKE_SOURCE_DIR "./" )
FILE(GLOB TARGET_H "${CMAKE_SOURCE_DIR}/*.h")
FILE(GLOB TARGET_CPP "${CMAKE_SOURCE_DIR}/*.cpp")
SET(TARGET_SRC ${TARGET_CPP} ${TARGET_H})
#file(GLOB_RECURSE sources_test src/test/*.cpp)
#file(GLOB_RECURSE data resources/*)
# you can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
# add_executable(DoJoystick ${sources} ${data}) # if you have data
add_executable(DoJoystick ${TARGET_SRC} ) # no data

# just for example add some compiler flags

target_compile_options(DoJoystick PUBLIC -Wall -Wextra -Wfloat-conversion)

# this lets me include files relative to the root source directory with a <> pair
#target_include_directories(DoJoystick PUBLIC src/main)

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executable
#file(COPY ${data} DESTINATION resources)

###############################################################################
## dependencies ###############################################################
###############################################################################

# this defines the variables Boost_LIBRARIES that contain all library names
# that we need to link to
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.74 COMPONENTS msm)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(DoJoystick ${Boost_LIBRARIES})
endif()

#find_package(Boost 1.74.0 COMPONENTS msm REQUIRED)
#
#target_link_libraries(DoJoystick PUBLIC
#        ${Boost_LIBRARIES}
#        # here you can add any library dependencies
#)

###############################################################################
## testing ####################################################################
###############################################################################
#
## this is for our testing framework
## we don't add REQUIRED because it's just for testing
#find_package(GTest)
#
#if(GTEST_FOUND)
#    add_executable(unit_tests ${sources_test} ${sources})
#
#    # we add this define to prevent collision with the main
#    # this might be better solved by not adding the source with the main to the
#    # testing target
#    target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)
#
#    # this allows us to use our executable as a link library
#    # therefore we can inherit all compiler options and library dependencies
#    set_target_properties(example PROPERTIES ENABLE_EXPORTS on)
#
#    target_link_libraries(unit_tests PUBLIC
#            ${GTEST_BOTH_LIBRARIES}
#            example
#    )
#
#    target_include_directories(unit_tests PUBLIC
#            ${GTEST_INCLUDE_DIRS} # doesn't do anything on Linux
#    )
#endif()

###############################################################################
## packaging ##################################################################
###############################################################################
#
## all install commands get the same destination. this allows us to use paths
## relative to the executable.
#install(TARGETS example DESTINATION example_destination)
## this is basically a repeat of the file copy instruction that copies the
## resources in the build directory, but here we tell CMake that we want it
## in the package
#install(DIRECTORY resources DESTINATION example_destination)
#
## now comes everything we need, to create a package
## there are a lot more variables you can set, and some
## you need to set for some package types, but we want to
## be minimal here
#set(CPACK_PACKAGE_NAME "MyExample")
#set(CPACK_PACKAGE_VERSION "1.0.0")
#
## we don't want to split our program up into several things
#set(CPACK_MONOLITHIC_INSTALL 1)
#
## This must be last
#include(CPack)