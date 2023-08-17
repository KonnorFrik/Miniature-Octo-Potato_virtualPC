#include "memory.hpp"

#include <iostream>

#include "architecture.hpp"
#include "settings.hpp"

void Memory::print_row(const int row) { std::cout << row << ": "; }

Memory::Memory(const int size) {
    this->size = size;
    this->memory = new Byte[size];

    nullify();
}

Memory::Memory(Memory& mem_obj) {
    this->memory = new Byte(mem_obj.size);

    for (int i = 0; i < mem_obj.size; ++i) {
        this->memory[i] = mem_obj[i];
    }
}

Memory::~Memory() { delete memory; }

void Memory::nullify() { fill(0); }

void Memory::fill(Byte value) {
    for (int i = 0; i < size; ++i) {
        memory[i] = value;
    }
}

void Memory::print_raw() {
    for (int i = 0; i < size; ++i) {
        std::cout << static_cast<short>(memory[i]) << " ";
    }
    std::cout << std::endl;
}

void Memory::print_hex() {
    short cols{0};
    int row{0};
    std::cout << std::hex << std::uppercase;
    print_row(row);

    for (int i = 0; i < size; ++i) {
        if (cols >= cols_per_row) {
            cols = 0;
            std::cout << std::endl;

            row++;
            print_row(row);
        }

        std::cout << static_cast<short>(memory[i]) << " ";
        cols++;
    }
    std::cout << std::dec << std::endl;
}

Byte& Memory::operator[](const int address) { return memory[address]; }
