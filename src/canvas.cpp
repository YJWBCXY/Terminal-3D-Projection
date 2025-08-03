#include "canvas.hpp"
#include "definitions.h"

Canvas::Canvas(const int x, const int y) {
    size_x = x;
    size_y = y;
    size = x * y;
    for (int i = 0; i < size; i++) {
        if (i % x == x - 1) {
            canvas.push_back('\n');
        } else {
            canvas.push_back(' ');
        }
        canvas_colours.emplace_back(WHITE);
        z_buffer.push_back(0.0);
    }
}

void Canvas::set(int index, char _char) {
    canvas[index] = _char;
}
void Canvas::set(int index, char _char, std::string& colour) {
    canvas[index] = _char;
    canvas_colours[index] = colour;
}

std::string Canvas::to_string() {
    std::string _string;
    for (int i = 0; i < size; i++) {
        _string += canvas_colours[i];
        _string.push_back(canvas[i]);
    }
    return _string;
}

void Canvas::clear() {
    for (int i = 0; i < size; i++) {
        canvas[i] = ' ';
        canvas_colours[i] = WHITE;
    }
}