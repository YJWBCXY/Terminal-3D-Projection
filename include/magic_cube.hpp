#pragma once

#if defined(_WIN32)
    #define _USE_MATH_DEFINES
    #include <cmath>
#endif

#include <vector>

#include "cube.hpp"

class Magic_cube {
    private:
    std::vector<Cube> cubes;
    double tmp_angle = 0, step = 0.1;
    int layer = 0;

    public:
    Magic_cube(double size);

    void rotate_x(double angle);
    void rotate_y(double angle);
    void rotate_z(double angle);

    void protate_x(double angle);
    void protate_y(double angle);
    void protate_z(double angle);

    void srotate_x(double angle);
    void srotate_y(double angle);
    void srotate_z(double angle);

    void move(double x, double y, double z);
    void pmove(double x, double y, double z);

    void draw(Canvas& canvas);

    void scramble();

    private:
    void update_scramble();
    void rotate_layer();
};