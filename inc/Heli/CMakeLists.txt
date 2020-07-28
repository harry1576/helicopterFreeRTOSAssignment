cmake_minimum_required(VERSION 3.10)
project(heli_api)

set(HELI_DIR ${PROJECT_SOURCE_DIR})

file(GLOB HELI_SOURCES
    ${PROJECT_SOURCE_DIR}/heli/*.c
)

add_library(${PROJECT_NAME} ${HELI_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE TivaWare)

target_include_directories(${PROJECT_NAME} INTERFACE ${HELI_DIR})
