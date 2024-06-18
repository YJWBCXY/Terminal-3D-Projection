#include "magic_cube.hpp"



Magic_cube::Magic_cube(double size) {
    double psize = size / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                // if (i == 1 && j == 1 && k == 1) {
                //     continue;
                // }
                Cube cube = Cube(psize);

                double x = 0, y = 0, z = 0;


                if (k == 0) {
                    x -= psize;
                } else if (k == 2) {
                    x += psize;
                }
                if (j == 0) {
                    y -= psize;
                } else if (j == 2) {
                    y += psize;
                }
                if (i == 0) {
                    z -= psize;
                } else if (i == 2) {
                    z += psize;
                }

                cube.pmove(x, y, z);

                cubes.push_back(cube);
            }
        }
    }
}

void Magic_cube::rotate_x(double angle) {
    for (Cube& cube : cubes) {
        cube.rotate_x(angle);
    }
}
void Magic_cube::rotate_y(double angle) {
    for (Cube& cube : cubes) {
        cube.rotate_y(angle);
    }
}
void Magic_cube::rotate_z(double angle) {
    for (Cube& cube : cubes) {
        cube.rotate_z(angle);
    }
}

void Magic_cube::protate_x(double angle) {
    for (Cube& cube : cubes) {
        cube.protate_x(angle);
    }
}
void Magic_cube::protate_y(double angle) {
    for (Cube& cube : cubes) {
        cube.protate_y(angle);
    }
}
void Magic_cube::protate_z(double angle) {
    for (Cube& cube : cubes) {
        cube.protate_z(angle);
    }
}

void Magic_cube::move(double x, double y, double z) {
    for (Cube& cube : cubes) {
        cube.move(x, y, z);
    }
}

void Magic_cube::pmove(double x, double y, double z) {
    for (Cube& cube : cubes) {
        cube.pmove(x, y, z);
    }
}

void Magic_cube::draw(Canvas& canvas) {
    for (Cube& cube : cubes) {
        cube.draw(canvas);
    }
}