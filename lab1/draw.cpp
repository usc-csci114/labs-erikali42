#include <iostream>
#include <fstream>
#include "drawing.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    Drawing drawing;
    drawing.parse(argv[1]);
    drawing.draw();
    drawing.write("output.bmp");

    return 0;
}
