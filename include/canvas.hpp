#pragma once

#include <string>
#include <vector>

class Canvas {
    private:
    int size;
    std::vector<char> canvas;
    std::vector<std::string> canvas_colours;

    public:
    int size_x, size_y;
    std::vector<double> z_buffer;

    Canvas(int x, int y);

    void set(int index, char _char);
    void set(int index, char _char, std::string& colour);

    std::string to_string();

    void clear();
};