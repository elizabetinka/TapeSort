//
// Created by Елизавета Кравченкова on 17.05.2024.
//
#include <lib/Tape.h>
#include <lib/TapeSorter.h>
#include <gtest/gtest.h>
#include <sstream>


void writeVectorInFile(const char* filename, const std::vector<int32_t>& vector) {

    std::ofstream fout(filename, std::ios::out);
    if (!fout.is_open()) {
        throw std::runtime_error("can't open file");
    }

    for (uint32_t i = 0; i < vector.size(); ++i) {
        fout << vector[i];
        if (i != (vector.size() - 1)) {
            fout << '\n';
        }

    }
    fout.close();
}

std::vector<int32_t> getVectorFromFile(const char* filename) {

    std::vector<int32_t> ans;
    std::ifstream fin(filename, std::ios::out);
    if (!fin.is_open()) {
        throw std::runtime_error("can't open file");
    }
    int32_t ch;

    while (fin >> ch) {
        ans.push_back(ch);
    }
    fin.close();
    return ans;
}

//"../../test/in.txt"
TEST(SortTapeTestSuite, SimpleSortTest) {
    std::vector<int32_t> vector = {1, 3, 24, 42145, 0, 13, 2, 5, 0, 9, 5, 6, 7, 3};
    writeVectorInFile("test/in.txt", vector);
    Tape tape = Tape("test/in.txt", 100, vector.size());
    TapeSorter::Sort(tape);
    std::sort(vector.begin(), vector.end());
    tape.Unload("test/out.txt");
    std::vector<int32_t> ans = getVectorFromFile("test/out.txt");
    ASSERT_EQ(vector, ans);
}


TEST(SortTapeTestSuite, CreateTape) {
    std::vector<int32_t> vector = {1, 3, 24, 42141, 0, 13, 2, 5, 0, 9, 5, 6, 7, 3};
    writeVectorInFile("test/in.txt", vector);
    Tape tape = Tape("test/in.txt", 100, vector.size());
    int idx = 1;
    ASSERT_EQ(vector[0], tape.Read());
    while (tape.MoveLeft()) {
        ASSERT_EQ(vector[idx], tape.Read());
        ++idx;
    }
}
