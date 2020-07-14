file(GLOB UTILS_SOURCES ustdlib.c uartstdio.c)
add_library(utils ${UTILS_SOURCES})
target_include_directories(utils PRIVATE ${TIVAWARE_DIR})