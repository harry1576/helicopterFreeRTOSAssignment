cmake_minimum_required(VERSION 3.10)
project(OrbitOLED)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/lib/*.c ${PROJECT_SOURCE_DIR}/lib/OrbitOled/*.h)
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE TivaWare)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/lib
    INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib>
)
