#include <iostream>
#include "stdint.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "parcing.h"
#include "lib/Tape.h"
#include "lib/TapeSorter.h"
#pragma comment( lib, "Pdh.lib" )
using json = nlohmann::json;
// command time -f '\nTime: %e s  Memory: %M KB'  -i test/in.txt -o test/out.txt -M 10




uint16_t  Tape::_write_delay;
uint16_t  Tape::_read_delay;
uint16_t  Tape::_rewind;
uint16_t  Tape::_move;



int main(int argc, char** argv) {
    getInfo arguments;
    Parsing(argc, argv, arguments);
    //std::cout << sizeof(arguments) << std::endl;
    std::ifstream f("config.json");
    json data = json::parse(f);
    //                                                    Tape::_write_delay +  Tape::_read_delay + Tape::_rewind + Tape::_move + Tape.mass + Tape.capacity + Tape.pos + Tape.filePos
    if (arguments.M <= (sizeof (data) + sizeof (getInfo) + 4* 2+ 4*8)){
        std::cerr<<"M must be more than " << sizeof(data) + sizeof (getInfo)+ 4* 2+ 4*8;
        return 1;
    }
    std::cout << "M: "<< arguments.M << "need:  "<< sizeof(data) + sizeof (getInfo)+ 4* 2+ 4*8 << std::endl;
    arguments.M -= sizeof(data) + sizeof (getInfo)+ 4* 2+ 4*8;

    Tape tape = Tape (arguments.inputFile,arguments.M,arguments.N);
    tape.SetSettings(data["write_delay"],data["read_delay"],data["rewind"],data["move"]);
    tape.Print();
    //tape.Paging();
    //tape.Print();
    //tape.Paging();
    //tape.Print();


    TapeSorter::Sort(tape);
    tape.Unload(arguments.outputFile);

    return 0;
}
