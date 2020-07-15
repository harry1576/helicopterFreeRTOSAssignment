cmake_minimum_required(VERSION 3.14)
project(FreeRTOS)

set(INC_SOURCES ${PROJECT_SOURCE_DIR}/include)

file(GLOB FREERTOS_SOURCES
    ${PROJECT_SOURCE_DIR}/*.c
    ${PROJECT_SOURCE_DIR}/portable/MemMang/heap_2.c
    ${PROJECT_SOURCE_DIR}/portable/GCC/ARM_CM4F/port.c
)

add_library(${PROJECT_NAME} ${FREERTOS_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
    PUBLIC ${PROJECT_SOURCE_DIR}/portable/GCC/ARM_CM4F
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

