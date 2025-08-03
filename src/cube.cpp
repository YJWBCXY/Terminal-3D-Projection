#include "cube.hpp"

Cube::Cube(double size) {
    SIZE = size;
    for (int i = 0; i < 6; i++) {
        Plane plane = Plane(SIZE, SIZE / 2, i);
        switch (i) {
            case PR_FRONT:
                plane.colour = RED;
                break;
            case PR_BACK:
                plane.colour = MAGENTA;
                break;
            case PR_RIGHT:
                plane.colour = GREEN;
                break;
            case PR_LEFT:
                plane.colour = BLUE;
                break;
            case PR_TOP:
                plane.colour = WHITE;
                break;
            case PR_BOTTOM:
                plane.colour = YELLOW;
                break;
        }
        planes.push_back(plane);
    }
}

std::vector<double> Cube::get_points(std::vector<double>& points_x,
                                     std::vector<double>& points_y,
                                     std::vector<double>& points_z) {
    points_x.clear();
    points_y.clear();
    points_z.clear();
    std::vector<double> dot_product;

    for (Plane plane : planes) {
        plane.calculate_dot_product();
        points_x.insert(points_x.end(),
                        plane.points_x.begin(),
                        plane.points_x.end());
        points_y.insert(points_y.end(),
                        plane.points_y.begin(),
                        plane.points_y.end());
        points_z.insert(points_z.end(),
                        plane.points_z.begin(),
                        plane.points_z.end());
        unsigned int size = plane.points_x.size();
        for (int i = 0; i < size; i++) {
            dot_product.push_back(plane.dot_product);
            colour.push_back(plane.colour);
        }
    }
    return dot_product;
}

void Cube::rotate_x(double angle) {
    for (Plane& plane : planes) {
        plane.rotate_x(angle);
    }
}
void Cube::rotate_y(double angle) {
    for (Plane& plane : planes) {
        plane.rotate_y(angle);
    }
}
void Cube::rotate_z(double angle) {
    for (Plane& plane : planes) {
        plane.rotate_z(angle);
    }
}

void Cube::protate_x(double angle) {
    for (Plane& plane : planes) {
        plane.protate_x(angle);
    }
}
void Cube::protate_y(double angle) {
    for (Plane& plane : planes) {
        plane.protate_y(angle);
    }
}
void Cube::protate_z(double angle) {
    for (Plane& plane : planes) {
        plane.protate_z(angle);
    }
}

void Cube::srotate_x(double angle) {
    for (Plane& plane : planes) {
        plane.srotate_x(angle);
    }
}
void Cube::srotate_y(double angle) {
    for (Plane& plane : planes) {
        plane.srotate_y(angle);
    }
}
void Cube::srotate_z(double angle) {
    for (Plane& plane : planes) {
        plane.srotate_z(angle);
    }
}

void Cube::crotate_x(bool reverse) {
    int clock[] = {PR_FRONT, PR_TOP, PR_BACK, PR_BOTTOM};
    int cclock[] = {PR_BOTTOM, PR_BACK, PR_TOP, PR_FRONT};
    int* faces;

    if (reverse) {
        faces = cclock;
    } else {
        faces = clock;
    }

    std::string first = planes[*faces].colour;

    for (int i = 0; i < 4; i++) {
        int index = *(faces + i);
        int index2;

        if (i + 1 < 4) {
            index2 = *(faces + i + 1);
            planes[index].colour = planes[index2].colour;
        } else {
            index2 = *faces;
            planes[index].colour = first;
        }
    }
}
void Cube::crotate_y(bool reverse) {
    int clock[] = {PR_FRONT, PR_RIGHT, PR_BACK, PR_LEFT};
    int cclock[] = {PR_LEFT, PR_BACK, PR_RIGHT, PR_FRONT};
    int* faces;

    if (reverse) {
        faces = cclock;
    } else {
        faces = clock;
    }

    std::string first = planes[*faces].colour;

    for (int i = 0; i < 4; i++) {
        int index = *(faces + i);
        int index2;

        if (i + 1 < 4) {
            index2 = *(faces + i + 1);
            planes[index].colour = planes[index2].colour;
        } else {
            index2 = *faces;
            planes[index].colour = first;
        }
    }
}
void Cube::crotate_z(bool reverse) {
    int cclock[] = {PR_TOP, PR_RIGHT, PR_BOTTOM, PR_LEFT};
    int clock[] = {PR_LEFT, PR_BOTTOM, PR_RIGHT, PR_TOP};
    int* faces;

    if (reverse) {
        faces = cclock;
    } else {
        faces = clock;
    }

    std::string first = planes[*faces].colour;

    for (int i = 0; i < 4; i++) {
        int index = *(faces + i);
        int index2;

        if (i + 1 < 4) {
            index2 = *(faces + i + 1);
            planes[index].colour = planes[index2].colour;
        } else {
            index2 = *faces;
            planes[index].colour = first;
        }
    }
}

void Cube::move(double x, double y, double z) {
    for (Plane& plane : planes) {
        plane.move(x, y, z);
    }
}

void Cube::pmove(double x, double y, double z) {
    for (Plane& plane : planes) {
        plane.pmove(x, y, z);
    }
}

void Cube::draw(Canvas& canvas) {
    for (Plane& plane : planes) {
        plane.no = no;
        plane.calculate_dot_product();
        plane.draw(canvas);
    }
    clear();
}

void Cube::clear() {
    for (Plane& plane : planes) {
        plane.clear();
    }
}

void Cube::colour_transfer(Cube& cube) {
    for (int i = 0; i < 6; i++) {
        planes[i].colour = cube.planes[i].colour;
    }
}