//
// Created by Елизавета Кравченкова on 15.05.2024.
//

#include "Tape.h"
#include <chrono>
#include <thread>

uint16_t  Tape::_write_delay;
uint16_t  Tape::_read_delay;
uint16_t  Tape::_rewind;
uint16_t  Tape::_move;

Tape::Tape(const char* filename, uint64_t capacity, uint64_t N) {
    _capacity = capacity / sizeof(value_type);
    _capacity = std::min(_capacity, N);
    if (_capacity < 1) {
        throw std::runtime_error("not enough capacity");
    }
    endIdx = _capacity;
    _filename = filename;
    mass = new int32_t[_capacity];
    std::ifstream fin(_filename);
    if (!fin.is_open()) {
        throw std::runtime_error("can't open file");
    }
    int32_t ch = 0;
    pos = 0;
    while (fin >> ch) {
        mass[pos] = ch;
        ++pos;
        if (pos == _capacity) {
            pos = 0;
            filePos = fin.tellg();
            break;
        }
    }
    pos = 0;
    fin.close();
}

void Tape::ChangeData(const char* filename) {
    _filename = filename;
    std::ifstream fin(_filename);
    if (!fin.is_open()) {
        throw std::runtime_error("can't open file");
    }
    int32_t ch = 0;
    pos = 0;
    while (fin >> ch) {
        mass[pos] = ch;
        ++pos;
        if (pos == _capacity) {
            pos = 0;
            filePos = fin.tellg();
            break;
        }
    }
    fin.close();
}

bool Tape::Paging() {
    std::ifstream fin(_filename);
    if (!fin.is_open()) {
        throw std::runtime_error("can't open file");
    }
    fin.seekg(filePos, std::ios_base::beg);
    int32_t ch = 0;
    pos = 0;
    bool flag = false;
    while (fin >> ch) {
        flag = true;
        mass[pos] = ch;
        ++pos;
        if (pos == _capacity) {
            filePos = fin.tellg();
            break;
        }
    }
    if (flag) {
        filePos = fin.tellg();
        endIdx = pos;
        pos = 0;
    } else {
        pos = endIdx - 1;
    }

    fin.close();
    return flag;
}

void Tape::SetSettings(uint16_t write_delay, uint16_t read_delay, uint16_t rewind, uint16_t move) {
    _write_delay = write_delay;
    _read_delay = read_delay;
    _rewind = rewind;
    _move = move;
}

void Tape::Write(int32_t value) {
    std::this_thread::sleep_for(std::chrono::milliseconds(_write_delay));
    mass[pos] = value;
}


int32_t Tape::Read() const {
    std::this_thread::sleep_for(std::chrono::milliseconds(_read_delay));
    return mass[pos];
}

void Tape::InBegin() {
    std::this_thread::sleep_for(std::chrono::milliseconds(_rewind));
    pos = 0;
}

// move tape to right mean get right elem
bool Tape::MoveLeft() {
    std::this_thread::sleep_for(std::chrono::milliseconds(_move));
    uint64_t tmp = pos;
    ++pos;
    if (pos == endIdx) {
        if (Paging()) {
            return true;
        }
        pos = tmp;
        return false;
    }
    return true;
}

// move tape to right mean get left elem
bool Tape::MoveRight() {
    std::this_thread::sleep_for(std::chrono::milliseconds(_move));
    if (pos == 0) {
        return false;
    }
    --pos;
    return true;
}

void Tape::Unload(const char* filename) {
    std::filesystem::remove(filename);
    std::filesystem::copy_file(_filename, filename);
}
