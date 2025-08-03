#include "plane.hpp"


Plane::Plane(double size, double z_offset) {
    SIZE_X = static_cast<int>(size / RESOLUTION),
    SIZE_Y = static_cast<int>(size / RESOLUTION);
    SIZE = SIZE_X * SIZE_Y;
    initial_points_x.resize(SIZE);
    initial_points_y.resize(SIZE);
    initial_points_z.resize(SIZE);
    initial_normal[2] = 1;
    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            int index = x + SIZE_X * y;
            initial_points_x[index] = x * RESOLUTION - RESOLUTION * SIZE_X / 2;
            initial_points_y[index] = y * RESOLUTION - RESOLUTION * SIZE_Y / 2;
            initial_points_z[index] = -z_offset;
        }
    }
    clear();
}

Plane::Plane(double size, double z_offset, int direction) {
    A = size;
    SIZE_X = static_cast<int>(size / RESOLUTION),
    SIZE_Y = static_cast<int>(size / RESOLUTION);
    SIZE = SIZE_X * SIZE_Y;
    initial_points_x.resize(SIZE);
    initial_points_y.resize(SIZE);
    initial_points_z.resize(SIZE);

    std::vector<double>* ptr_1;
    std::vector<double>* ptr_2;
    std::vector<double>* ptr_flat;
    int offset_direction = 1;

    switch (direction) {
        case PR_FRONT:
            ptr_1 = &initial_points_x;
            ptr_2 = &initial_points_y;
            ptr_flat = &initial_points_z;
            offset_direction = -1;
            initial_normal[2] = 1;
            break;
        case PR_BACK:
            ptr_1 = &initial_points_x;
            ptr_2 = &initial_points_y;
            ptr_flat = &initial_points_z;
            initial_normal[2] = -1;
            break;
        case PR_RIGHT:
            ptr_1 = &initial_points_y;
            ptr_2 = &initial_points_z;
            ptr_flat = &initial_points_x;
            initial_normal[0] = -1;
            break;
        case PR_LEFT:
            ptr_1 = &initial_points_y;
            ptr_2 = &initial_points_z;
            ptr_flat = &initial_points_x;
            offset_direction = -1;
            initial_normal[0] = 1;
            break;
        case PR_TOP:
            ptr_1 = &initial_points_x;
            ptr_2 = &initial_points_z;
            ptr_flat = &initial_points_y;
            offset_direction = -1;
            initial_normal[1] = 1;
            break;
        case PR_BOTTOM:
            ptr_1 = &initial_points_x;
            ptr_2 = &initial_points_z;
            ptr_flat = &initial_points_y;
            initial_normal[1] = -1;
            break;
    }

    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            int index = x + SIZE_X * y;
            ptr_1->at(index) =
                x * RESOLUTION - RESOLUTION * SIZE_X / 2 + RESOLUTION / 2;
            ptr_2->at(index) =
                y * RESOLUTION - RESOLUTION * SIZE_Y / 2 + RESOLUTION / 2;
            ptr_flat->at(index) = z_offset * offset_direction;
        }
    }
    clear();
}

void Plane::calculate_dot_product() {
    dot_product = 0;
    for (int i = 0; i < 3; i++) {
        dot_product += normal[i] * view[i];
    }
}

void Plane::rotate_x(double angle) {
    rotation_x += angle;
    double rotation = rotation_x /*+ (double)pi_2_rotation_x * M_PI_2*/;
    for (int i = 0; i < SIZE; i++) {
        rotate_x(rotation, points_y[i], points_z[i]);
    }
    rotate_x(rotation, normal[1], normal[2]);
}
void Plane::rotate_y(double angle) {
    rotation_y += angle;
    double rotation = rotation_y /*+ (double)pi_2_rotation_y * M_PI_2*/;
    for (int i = 0; i < SIZE; i++) {
        rotate_y(rotation, points_x[i], points_z[i]);
    }
    rotate_y(rotation, normal[0], normal[2]);
}
void Plane::rotate_z(double angle) {
    rotation_z += angle;
    double rotation = rotation_z /*+ (double)pi_2_rotation_z * M_PI_2*/;
    for (int i = 0; i < SIZE; i++) {
        rotate_z(rotation, points_x[i], points_y[i]);
    }
    rotate_z(rotation, normal[0], normal[1]);
}

void Plane::protate_x(double angle) {
    for (int i = 0; i < SIZE; i++) {
        rotate_x(angle, initial_points_y[i], initial_points_z[i]);
    }
    rotate_x(angle, initial_normal[1], initial_normal[2]);
}
void Plane::protate_y(double angle) {
    for (int i = 0; i < SIZE; i++) {
        rotate_y(angle, initial_points_x[i], initial_points_z[i]);
    }
    rotate_y(angle, initial_normal[0], initial_normal[2]);
}
void Plane::protate_z(double angle) {
    for (int i = 0; i < SIZE; i++) {
        rotate_z(angle, initial_points_x[i], initial_points_y[i]);
    }
    rotate_z(angle, initial_normal[0], initial_normal[1]);
}

void Plane::srotate_x(double angle) {
    double rotation = /*rotation_x +*/ angle;
    for (int i = 0; i < SIZE; i++) {
        rotate_x(rotation, points_y[i], points_z[i]);
    }
    rotate_x(rotation, normal[1], normal[2]);
}
void Plane::srotate_y(double angle) {
    double rotation = /*rotation_y +*/ angle;
    for (int i = 0; i < SIZE; i++) {
        rotate_y(rotation, points_x[i], points_z[i]);
    }
    rotate_y(rotation, normal[0], normal[2]);
}
void Plane::srotate_z(double angle) {
    double rotation = /*rotation_z +*/ angle;
    for (int i = 0; i < SIZE; i++) {
        rotate_z(rotation, points_x[i], points_y[i]);
    }
    rotate_z(rotation, normal[0], normal[1]);
}

void Plane::move(double x, double y, double z) {
    for (int i = 0; i < SIZE; i++) {
        points_x[i] += x;
        points_y[i] += y;
        points_z[i] += z;
    }
}
void Plane::pmove(double x, double y, double z) {
    for (int i = 0; i < SIZE; i++) {
        initial_points_x[i] += x;
        initial_points_y[i] += y;
        initial_points_z[i] += z;
    }
}

void Plane::draw(Canvas& canvas) {
    int x = (std::min)(canvas.size_x, canvas.size_y);
    double depth = (double)A / ((double)canvas.size_y * 0.005);
    double fov = 50;

    for (int point = 0; point < SIZE; point++) {
        double inverse_z = 1 / ((points_z[point]) + depth);
        int pint_x =
            (int)(canvas.size_x / 2.0 + fov * inverse_z * (points_x[point]));
        int point_y = (int)(canvas.size_y / 1.95 +
                            (fov / 2) * inverse_z * (points_y[point]));

        int index = pint_x + canvas.size_x * point_y;
        int normal = (int)(8 * (dot_product));
        if (point_y < canvas.size_y && point_y >= 0 && pint_x >= 0 &&
            pint_x <= canvas.size_x - 1 && inverse_z > canvas.z_buffer[index]) {
            canvas.z_buffer[index] = inverse_z;
            char _char;

            if (normal > 0) {
                _char = ".,-~:;=!*#$@"[normal];
            } else {
                _char = '.';
            }

            /* for debugging uncomment the line below */
            // _char = no + '@';

            canvas.set(index, _char, colour);
        }
    }
}

void Plane::clear() {
    points_x = initial_points_x;
    points_y = initial_points_y;
    points_z = initial_points_z;
    for (int i = 0; i < 3; i++) {
        normal[i] = initial_normal[i];
    }
}