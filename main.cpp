#include <iostream>
#include <nlohmann/json.hpp>
#include "parcing.h"
#include "lib/Tape.h"
#include "lib/TapeSorter.h"
#pragma comment( lib, "Pdh.lib" )
using json = nlohmann::json;



int main(int argc, char** argv) {
    getInfo arguments;
    Parsing(argc, argv, arguments);
    std::ifstream f("config.json");
    json data = json::parse(f);
    //                                                    variables in Tape
    if (arguments.M <= (sizeof (data) + sizeof (getInfo) + 48)){
        std::cerr<<"M must be more than " << sizeof(data) + sizeof (getInfo)+ 48;
        return 1;
    }
    std::cout << "M: "<< arguments.M << "need:  "<< sizeof(data) + sizeof (getInfo)+ 48 << std::endl;
    arguments.M -= sizeof(data) + sizeof (getInfo)+ 48;

    Tape tape = Tape (arguments.inputFile,arguments.M,arguments.N);
    tape.SetSettings(data["write_delay"],data["read_delay"],data["rewind"],data["move"]);
    TapeSorter::Sort(tape);
    tape.Unload(arguments.outputFile);

    return 0;
}
