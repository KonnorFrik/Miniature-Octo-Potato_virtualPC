#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "memory.hpp"
#include "settings.hpp"
#include "utils.hpp"

//int load_rom_to_mem(const std::string& filename, Memory& mem, int mem_size, Byte& start_addr_out) {
int load_rom_to_mem(const std::string& filename, Memory& mem, Byte& start_addr_out) {
    std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
    std::streampos size;

    char* memblock;
    int status_code = 0;

    if (file.is_open()) {
        size = file.tellg();
        //start_addr_out = rand() % (mem_size - size);
        start_addr_out = 0;
        memblock = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);

        file.close();
    } else {
        std::cout << "File not opened for uncknown reason" <<  std::endl;
        status_code = 1;
    }

    for (int ind = start_addr_out, i = 0; i < size; ++i, ++ind) {
        mem[ind] = memblock[i];
    }

    delete memblock;
    return status_code;
}
