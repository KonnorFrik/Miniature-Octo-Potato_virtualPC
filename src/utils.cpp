#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "memory.hpp"
#include "settings.hpp"

void load_rom_to_mem(const std::string& filename, Memory& mem) {
    std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
    std::streampos size;

    char* memblock;

    if (file.is_open()) {
        size = file.tellg();
        memblock = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();
    } else if (DEBUG) {
        std::cout << "[DEBUG] File not open" << std::endl;
    }

    for (int i = 0; i < size; ++i) {
        mem[i] = memblock[i];
    }

    delete memblock;
}
