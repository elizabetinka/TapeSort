//
// Created by Елизавета Кравченкова on 17.05.2024.
//
#include <lib/Tape.h>
#include <lib/TapeSorter.h>
#include <gtest/gtest.h>
#include <sstream>


void writeVectorInFile(const char * filename,const std::vector<int32_t>& vector ) {

    std::ofstream fout(filename, std::ios::out);
    for (uint32_t i = 0; i < vector.size(); ++i) {
        fout<<vector[i];

    }
    fout.close();
}


TEST(SortTapeTestSuite, SimpleTest) {
    std::vector<int32_t> vector = {1,3,24,42141,0,13,2,5,0,9,5,6,7,3};
    writeVectorInFile("test/in.txt",vector);
    Tape tape = Tape ("test/in.txt",100,vector.size());
    TapeSorter::Sort(tape);
    std::sort(vector.begin(),vector.end());
    int idx=0;
    while (tape.MoveLeft()){
        ASSERT_EQ(vector[idx],tape.Read());
    }
}
