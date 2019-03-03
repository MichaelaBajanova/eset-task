#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid number of parameters.\n";
        return EXIT_FAILURE;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Invalid file.\n";
        return EXIT_FAILURE;
    }

    Parser parser = Parser();
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        if (line.find("name=\"") != 0) {
            continue;
        }

        parser.parseAndPrint(line);
    }

    return 0;
}