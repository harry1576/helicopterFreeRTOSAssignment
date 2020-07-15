cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(tiva-toolchain)

project(firmware)

include(tiva)
include(docs)
add_subdirectory(TivaWare)
add_subdirectory(inc/OrbitOLED)
add_subdirectory(inc/FreeRTOS)

file(GLOB SOURCES src/*.c src/*.h)

add_executable(${CMAKE_PROJECT_NAME}.elf ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}.elf TivaWare OrbitOLED FreeRTOS)
