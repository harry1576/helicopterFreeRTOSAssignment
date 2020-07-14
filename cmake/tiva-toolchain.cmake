set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX "arm-none-eabi")

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-as)
set(CMAKE_AR ${TOOLCHAIN_PREFIX}-ar)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}-objdump)

set(CPU "-mcpu=cortex-m4")
set(FPU "-mfpu=fpv4-sp-d16 -mfloat-abi=softfp")
set(CMAKE_ASM_FLAGS " -mthumb ${CPU} ${FPU} -MD")
set(CMAKE_C_FLAGS "-mthumb ${CPU} ${FPU} -std=gnu18 -O0 -ffunction-sections -fdata-sections -Wall -pedantic")
set(CMAKE_CXX_FLAGS "-mthumb ${CPU} ${FPU} -Os -ffunction-sections -fdata-sections -MD -Wall -pedantic -fno-exceptions -fno-rtti")

set(CMAKE_EXE_LINKER_FLAGS "--static -T${CMAKE_SOURCE_DIR}/inc/tiva_linkers/tm4c123gh6pm.lds -specs=${CMAKE_SOURCE_DIR}/inc/tiva_linkers/tiva.specs -specs=nosys.specs")

