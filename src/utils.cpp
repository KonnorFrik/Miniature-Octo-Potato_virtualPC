#include <fstream>
#include <iostream>
#include <string>

#include "architecture.hpp"
#include "memory.hpp"
#include "settings.hpp"
#include "utils.hpp"

int load_rom_to_mem(const std::string& filename, Memory& mem, int mem_size, Byte& start_addr_out) {
//int load_rom_to_mem(const std::string& filename, Memory& mem, Byte& start_addr_out) {
    std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
    std::streampos size{0};

    char* memblock;
    int status_code{0};
    int programm_size{0};

    if (file.is_open()) {
        size = file.tellg();
        memblock = new char[size]; // all programm and header here
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();

        programm_size = static_cast<int>(size) - HEADER_SIZE;
        start_addr_out = memblock[0];

    } else {
        std::cout << "File not opened for unknown reason" <<  std::endl;
        status_code = 1;
    }


    for (int ind = start_addr_out, i = 0; i < programm_size && ind < mem_size; ++i, ++ind) {
        mem[ind] = memblock[i + HEADER_SIZE];
    }

    delete memblock;
    return status_code;
}
