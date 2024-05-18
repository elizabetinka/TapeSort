//
// Created by Елизавета Кравченкова on 16.05.2024.
//

#pragma once

#include "Tape.h"
#include <filesystem>
#include <sstream>

class TapeSorter {
public:
    void static Sort(ITape& tape);

private:
    std::string static CreatePath(uint32_t k);

    bool static existKhook(uint32_t k);

    void static WriteSortListFrom2File(const char* file1, const char* file2, uint64_t count, const char* outfile);

    void static WriteSortListFromFile(const char* file1, const char* file2, const char* outfile);

    void static hang(uint32_t k, const char* filename);

    uint32_t static countFilesInDir(const char* name);
};