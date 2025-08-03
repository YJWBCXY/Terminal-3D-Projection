#pragma once

#if defined(_WIN32)
    #define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <vector>

#include "canvas.hpp"
#include "definitions.h"

class Plane {
    private:
    int SIZE_X, SIZE_Y;
    double A;
    double RESOLUTION = 0.05;
    double rotation_x = 0, rotation_y = 0, rotation_z = 0;
    std::vector<double> initial_points_x, initial_points_y, initial_points_z;
    double initial_normal[3] = {0, 0, 0}; // x, y, z
    int SIZE;
    double normal[3] = {0, 0, 0}; // x, y, z
    double view[3] = {0, 1, 1};   // x, y, z

    public:
    std::vector<double> points_x, points_y, points_z;
    double dot_product;
    std::string colour = WHITE;
    int no;

    Plane(double size, double z_offset);
    Plane(double size, double z_offset, int direction);
    void calculate_dot_product();

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

    void clear();

    static void rotate_x(double angle, double& y, double& z) {
        double sin_alpha = sin(angle);
        double cos_alpha = cos(angle);
        double tmp_y = y;
        y = y * cos_alpha - z * sin_alpha;
        z = tmp_y * sin_alpha + z * cos_alpha;
    }
    static void rotate_y(double angle, double& x, double& z) {
        double sin_beta = sin(angle);
        double cos_beta = cos(angle);
        double tmp_x = x;
        x = tmp_x * cos_beta + z * sin_beta;
        z = -tmp_x * sin_beta + z * cos_beta;
    }
    static void rotate_z(double angle, double& x, double& y) {
        double sin_gamma = sin(angle);
        double cos_gamma = cos(angle);
        double tmp_x = x;
        x = tmp_x * cos_gamma - y * sin_gamma;
        y = tmp_x * sin_gamma + y * cos_gamma;
    }
};