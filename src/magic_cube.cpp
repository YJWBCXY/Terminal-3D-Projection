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

                double x = 0;
                double y = 0;
                double z = 0;


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
                cube.no = k + j * 3 + i * 9;
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

void Magic_cube::srotate_x(double angle) {
    for (Cube& cube : cubes) {
        cube.srotate_x(angle);
    }
}
void Magic_cube::srotate_y(double angle) {
    for (Cube& cube : cubes) {
        cube.srotate_y(angle);
    }
}
void Magic_cube::srotate_z(double angle) {
    for (Cube& cube : cubes) {
        cube.srotate_z(angle);
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
        // if (cube.no >= 6 && cube.no <= 8 || cube.no >= 15 && cube.no <= 17 ||
        // cube.no >= 24 && cube.no <= 26 || cube.no == 10) {
        cube.draw(canvas);
        // }
    }
}

void Magic_cube::scramble() {
    update_scramble();
    rotate_layer();
}

void Magic_cube::update_scramble() {
    tmp_angle += step;
    std::vector<Cube> tmp_cubes;
    tmp_cubes.assign(cubes.begin(), cubes.end());
    if (tmp_angle > M_PI_2) {
        tmp_angle = 0;
        for (int z = 0; z < 3; z++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    int index = x + y * 3 + z * 9;
                    switch (layer) {
                        case FRONT:
                            if (z == 0) {
                                cubes[index].crotate_z(false);
                                tmp_cubes[(2 - y) + x * 3 + z * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;

                        case BACK: // back prim
                            if (z == 2) {
                                cubes[index].crotate_z(false);
                                tmp_cubes[(2 - y) + x * 3 + z * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case UP: // down prim
                            if (y == 2) {
                                cubes[index].crotate_y(false);
                                tmp_cubes[z + y * 3 + (2 - x) * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case DOWN:
                            if (y == 0) {
                                cubes[index].crotate_y(false);
                                tmp_cubes[z + y * 3 + (2 - x) * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case LEFT:
                            if (x == 0) {
                                cubes[index].crotate_x(false);
                                tmp_cubes[x + (2 - z) * 3 + y * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case RIGHT:
                            if (x == 2) {
                                cubes[index].crotate_x(false);
                                tmp_cubes[x + (2 - z) * 3 + y * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case MIDDLE:
                            if (x == 1) {
                                cubes[index].crotate_x(false);
                                tmp_cubes[x + (2 - z) * 3 + y * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case EQUATOR:
                            if (y == 1) {
                                cubes[index].crotate_y(false);
                                tmp_cubes[z + y * 3 + (2 - x) * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case STANDING:
                            if (z == 1) {
                                cubes[index].crotate_z(false);
                                tmp_cubes[(2 - y) + x * 3 + z * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_FRONT:
                            if (z == 0) {
                                cubes[index].crotate_z(true);
                                tmp_cubes[y + (2 - x) * 3 + z * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_BACK:
                            if (z == 2) {
                                cubes[index].crotate_z(true);
                                tmp_cubes[y + (2 - x) * 3 + z * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_UP:
                            if (y == 2) {
                                cubes[index].crotate_y(true);
                                tmp_cubes[(2 - z) + y * 3 + x * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_DOWN:
                            if (y == 0) {
                                cubes[index].crotate_y(true);
                                tmp_cubes[(2 - z) + y * 3 + x * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_LEFT:
                            if (x == 0) {
                                cubes[index].crotate_x(true);
                                tmp_cubes[x + z * 3 + (2 - y) * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_RIGHT:
                            if (x == 2) {
                                cubes[index].crotate_x(true);
                                tmp_cubes[x + z * 3 + (2 - y) * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_MIDDLE:
                            if (x == 1) {
                                cubes[index].crotate_x(true);
                                tmp_cubes[x + z * 3 + (2 - y) * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_EQUATOR:
                            if (y == 1) {
                                cubes[index].crotate_y(true);
                                tmp_cubes[(2 - z) + y * 3 + x * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                        case PRIME_STANDING:
                            if (z == 1) {
                                cubes[index].crotate_z(true);
                                tmp_cubes[y + (2 - x) * 3 + z * 9]
                                    .colour_transfer(cubes[index]);
                            }
                            break;
                    }
                }
            }
        }
        cubes.assign(tmp_cubes.begin(), tmp_cubes.end());
        layer = rand() % 18;
        // layer = 2;
    }
}

void Magic_cube::rotate_layer() {
    for (int z = 0; z < 3; z++) {
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                switch (layer) {
                    case FRONT:
                        if (z == 0) {
                            cubes[x + y * 3 + z * 9].srotate_z(tmp_angle);
                        }
                        break;

                    case BACK:
                        if (z == 2) {
                            cubes[x + y * 3 + z * 9].srotate_z(tmp_angle);
                        }
                        break;
                    case UP:
                        if (y == 2) {
                            cubes[x + y * 3 + z * 9].srotate_y(tmp_angle);
                        }
                        break;
                    case DOWN:
                        if (y == 0) {
                            cubes[x + y * 3 + z * 9].srotate_y(tmp_angle);
                        }
                        break;
                    case LEFT:
                        if (x == 0) {
                            cubes[x + y * 3 + z * 9].srotate_x(tmp_angle);
                        }
                        break;
                    case RIGHT:
                        if (x == 2) {
                            cubes[x + y * 3 + z * 9].srotate_x(tmp_angle);
                        }
                        break;
                    case MIDDLE:
                        if (x == 1) {
                            cubes[x + y * 3 + z * 9].srotate_x(tmp_angle);
                        }
                        break;
                    case EQUATOR:
                        if (y == 1) {
                            cubes[x + y * 3 + z * 9].srotate_y(tmp_angle);
                        }
                        break;
                    case STANDING:
                        if (z == 1) {
                            cubes[x + y * 3 + z * 9].srotate_z(tmp_angle);
                        }
                        break;
                    case PRIME_FRONT:
                        if (z == 0) {
                            cubes[x + y * 3 + z * 9].srotate_z(-tmp_angle);
                        }
                        break;
                    case PRIME_BACK:
                        if (z == 2) {
                            cubes[x + y * 3 + z * 9].srotate_z(-tmp_angle);
                        }
                        break;
                    case PRIME_UP:
                        if (y == 2) {
                            cubes[x + y * 3 + z * 9].srotate_y(-tmp_angle);
                        }
                        break;
                    case PRIME_DOWN:
                        if (y == 0) {
                            cubes[x + y * 3 + z * 9].srotate_y(-tmp_angle);
                        }
                        break;
                    case PRIME_LEFT:
                        if (x == 0) {
                            cubes[x + y * 3 + z * 9].srotate_x(-tmp_angle);
                        }
                        break;
                    case PRIME_RIGHT:
                        if (x == 2) {
                            cubes[x + y * 3 + z * 9].srotate_x(-tmp_angle);
                        }
                        break;
                    case PRIME_MIDDLE:
                        if (x == 1) {
                            cubes[x + y * 3 + z * 9].srotate_x(-tmp_angle);
                        }
                        break;
                    case PRIME_EQUATOR:
                        if (y == 1) {
                            cubes[x + y * 3 + z * 9].srotate_y(-tmp_angle);
                        }
                        break;
                    case PRIME_STANDING:
                        if (z == 1) {
                            cubes[x + y * 3 + z * 9].srotate_z(-tmp_angle);
                        }
                        break;
                }
            }
        }
    }
}