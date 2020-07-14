cmake_minimum_required(VERSION 3.14)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(tiva-toolchain)

project(tiva_code)

include(tiva)
add_subdirectory(TivaWare)
add_subdirectory(inc/OrbitOLED)

file(GLOB SOURCES src/*.c src/*.h)

add_executable(${CMAKE_PROJECT_NAME}.axf ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}.axf TivaWare OrbitOLED)
