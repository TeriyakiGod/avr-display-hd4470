cmake_minimum_required(VERSION 3.0.0)
project(avr-counter VERSION 0.1.0 LANGUAGES C)

set(MMCU "atmega16")
set(CMAKE_C_COMPILER "avr-gcc")
set(CMAKE_CXX_COMPILER "avr-g++")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=${MMCU}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmcu=${MMCU}")

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

add_executable(avr-counter src/main.c)
set_target_properties(avr-counter PROPERTIES ENABLE_EXPORTS OFF)