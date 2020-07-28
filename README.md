# Tiva CMake (Now with FreeRTOS)
Yay! CCS is no more CMake is here to save you.

## Building
```bash
user@linux~$ mkdir build
user@linux~$ cd build
user@linux~$ cmake ..
user@linux~$ make
```
## Flashing
```bash
user@linux~$ make flash
```

## Differences from stock repo
This uses CMake so have some differences compared to the demo repo, this was made before that so for example this linker script is more complex. The CMakeLists.txt and files in [cmake](cmake) folder decribe the building of the project

## Heli Lib
To simplify the code as much as possible using a separate heli library found in [inc/Heli](inc/Heli)

## Demo Code
The original demo code from Andre's repo can be found in [demo-code/](demo_
code)

## Debugging
Using VScode plus the cortex-debug extension should enable debugging.

## Authors
-   Jos Craw
-   Joshua Hulbert
-   Harry Dobbs
