file(GLOB DRIVERLIB_SOURCES *.c)
add_library(driverlib ${DRIVERLIB_SOURCES})
target_include_directories(driverlib PRIVATE ${TIVAWARE_DIR})
