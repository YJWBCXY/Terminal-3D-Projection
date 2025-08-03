#if defined(_WIN32)
    #define _USE_MATH_DEFINES
#endif

// #include <algorithm>
#include <chrono>
// #include <cmath>
#include <iostream>
// #include <numbers>
// #include <string>
#include <thread>
// #include <vector>

#if defined(__linux__) || defined(__APPLE__)
    // #include <stdio.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

#include "canvas.hpp"
#include "cube.hpp"
// #include "definitions.h"
#include "magic_cube.hpp"
// #include "plane.hpp"

#define RX 80
#define RY 24

#define R1 1
#define R2 2

#define PLANE_STEP 0.0145

void magic_cube_draw(Magic_cube& magic_cube, Canvas& canvas) {
    magic_cube.scramble();
    magic_cube.rotate_y(0.02);
    magic_cube.rotate_x(0.01);
    magic_cube.draw(canvas);
}


void ascii_frame() {
    double rotation_x = 0;
    double rotation_z = 0;
    int terminal_x = RX;
    int terminal_y = RY;
    Cube cube = Cube(3);
    Magic_cube magic_cube = Magic_cube(3);


    while (true) {
#if defined(__linux__) || defined(__APPLE__)
        struct winsize window;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
        terminal_x = window.ws_col;
        terminal_y = window.ws_row;
#elif defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        terminal_x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        terminal_y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif
        Canvas canvas = Canvas(terminal_x, terminal_y--);

        magic_cube_draw(magic_cube, canvas);
        std::cout << "\033[H\033[J"; // Clear the terminal
        std::cout << canvas.to_string();
        canvas.clear();

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}

int main() {
#if defined(_WIN32)
    system("color");
#endif

    ascii_frame();
    return 0;
}