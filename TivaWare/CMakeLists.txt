cmake_minimum_required(VERSION 3.14)
project(TivaWare)

set(TIVAWARE_DIR ${PROJECT_SOURCE_DIR})

add_subdirectory(driverlib)
add_subdirectory(utils)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE driverlib utils)
target_include_directories(${PROJECT_NAME} INTERFACE ${TIVAWARE_DIR})
