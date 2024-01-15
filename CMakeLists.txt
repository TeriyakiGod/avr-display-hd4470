cmake_minimum_required(VERSION 3.0.0)
project(avr-display-hd4470 C)

set(MMCU "atmega16")
set(F_CPU "16000000UL")
set(CMAKE_C_COMPILER "avr-gcc")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=${MMCU} -DF_CPU=${F_CPU} -Os")

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

add_executable(avr-display-hd4470 ${SOURCES})

set_target_properties(avr-display-hd4470 PROPERTIES ENABLE_EXPORTS OFF)