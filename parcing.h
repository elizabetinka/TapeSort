//
// Created by Елизавета Кравченкова on 16.05.2024.
//

#pragma once

#include "stdint.h"

struct getInfo {
    char* inputFile; // 8 byte
    char* outputFile; // 8 byte
    uint64_t M = UINT64_MAX; // 8 byte
    uint32_t N; // 4 byte
};

void Parsing(int argc, char** argv, getInfo& arguments);
