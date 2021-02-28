# csnake

The **c**onsole **snake** is a simple implementation of snake game written in C++ with optional TUI written with ncurses.

## Compiling

The easiest way to compile this library is to use cmake. If you set cmake option `NO_TUI` to `ON`, rendering class will not be compiled into library file. In this case you should also define `CSNAKE_NO_TUI` before including header file *csnake.hpp* to your project.