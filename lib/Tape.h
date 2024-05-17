//
// Created by Елизавета Кравченкова on 15.05.2024.
//

#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "stdint.h"
#include <cmath>

class ITape {
public:

    ITape()=default;

    virtual int32_t Read() const = 0;

    virtual void ChangeData(const char* filename) = 0;


    virtual void SetSettings(uint16_t write_delay,uint16_t read_delay,uint16_t rewind,uint16_t move) = 0;

    virtual void Write(int32_t value) = 0;

    virtual bool MoveRight()  = 0;

    virtual bool MoveLeft()  = 0;

    virtual void InBegin() = 0;

    virtual ~ITape() = default;
};

class Tape : public ITape {
    typedef int32_t value_type;
public:
    Tape();

    Tape(const char * filename,uint64_t capacity ,uint64_t N );


    void ChangeData(const char* filename);

    void SetSettings(uint16_t write_delay,uint16_t read_delay,uint16_t rewind,uint16_t move);

    void Write(value_type value);

    bool MoveRight() ;

    bool MoveLeft();

    void InBegin() ;

    void Unload(const char * filename);

    bool Paging();

    void Print(){
        for (uint64_t i=0; i< endIdx; ++i) {
            std::cout<<mass[i]<<" ";
        }
    }

    value_type Read() const;


    ~Tape() noexcept {
        if (mass != nullptr){
            delete [] mass;
        }
    }


private:
    static uint16_t _write_delay;
    static uint16_t _read_delay;
    static uint16_t _rewind;
    static uint16_t _move;
    const char* _filename;
    value_type* mass;
    uint64_t _capacity;
    uint64_t filePos=0;
    uint64_t pos=0;
    uint64_t endIdx=0;
};





