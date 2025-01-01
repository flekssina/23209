#include "CSVParser.h"
#include "TuplePrinter.h" // Для вывода кортежей
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./lab4 <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        CSVParser<int, std::string, std::string> parser(file, 1, ',');
        for (const auto& row : parser) {
          
            std::cout << row << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
