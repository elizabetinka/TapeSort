//
// Created by Елизавета Кравченкова on 16.05.2024.
//

#include "parcing.h"
#include <fstream>
#include <iostream>


// lines = count "\n" + 1
uint32_t lines(const char *path) {
    std::ifstream fin(path);

    char s;
    uint32_t counter = 1;
    while (fin.get(s)) {
        if (s == '\n') {
            ++counter;
        }
    }
    return counter;
}


void Parsing(int argc, char** argv, getInfo& arguments) {
    bool boolIn = false;
    bool boolOut = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-M") == 0 or strcmp(argv[i], "--ram") == 0) {
            i++;
            arguments.M = static_cast<uint64_t>(atoi(argv[i]));
        }
        else if (strcmp(argv[i], "-i") == 0 or strcmp(argv[i], "--input") == 0) {
            i++;
            arguments.inputFile = argv[i];
            boolIn=true;
        } else if (strcmp(argv[i], "-o") == 0 or strcmp(argv[i], "--output") == 0) {
            i++;
            arguments.outputFile = argv[i];
           boolOut = true;
        }
        else {
            std::cerr << "unknown option" << std::endl;
        }
    }
    // check urequired parameters
    if (!boolIn|| !boolOut) {
        std::cerr << "urequired parameters were not entered" << std::endl;
        exit(1);
    }
    arguments.N = lines(arguments.inputFile);
}
