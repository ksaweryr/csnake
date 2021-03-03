# csnake

The **c**onsole **snake** is a simple implementation of snake game written in C++ with optional TUI written with ncurses.

## Compiling

The easiest way to compile this library is to use cmake. If you set cmake option `NO_TUI` to `ON`, rendering class will not be compiled into library file. In this case you should also define `CSNAKE_NO_TUI` before including header file `csnake.hpp` to your project.

## Running regular snake game

Create file `main.cpp` with following content:

`
#include <csnake.hpp>
int main() {
	csnake::run();
}
`

Compile library, then compile executable with `$ g++ main.cpp libcsnake.a -lncurses -o snake` and execute with `$ ./snake`