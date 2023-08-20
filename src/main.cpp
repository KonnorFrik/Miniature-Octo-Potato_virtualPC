#include <cmath>
#include <iostream>
#include <string>

#include "cpu.hpp"
#include "memory.hpp"
#include "settings.hpp"
#include "utils.hpp"
//#include "architecture.hpp"

#define DEBUG_ARG_WORD "debug"
#define ROM_NAME "programms/memory.rom"

int main(int argc, char* argv[]) {
    std::string filename;
    std::string this_prog_name{argv[0]};
    bool cpu_debug_flag{false};

    if (argc < 2) {
        std::cout << "filename with programm not given" << std::endl;
        exit(BAD_ARGS_CODE);

    } else {
        for (int i = 0; i < argc; ++i) {
            std::string buf{argv[i]};
            if (buf == DEBUG_ARG_WORD && buf != this_prog_name) {
                cpu_debug_flag = true;
                continue;
            }

            if (buf != DEBUG_ARG_WORD && buf != this_prog_name) {
                filename = buf;
                continue;
            }
        }
    }

    // std::string filename = argc >= 2 ? argv[1] : ROM_NAME;

    if (DEBUG) {
        std::cout << "[DEBUG]" << std::endl;
        std::cout << "\tthis programm: " << this_prog_name << std::endl;
        std::cout << "\tFilename: " << filename << std::endl;
        std::cout << "\tCpu debug: " << cpu_debug_flag << std::endl;
        std::cout << std::endl;
    }

    int size = pow(2, CPU_BITS);
    Memory memory(size);

    /***Programm here***/
    // memory[0x00] = 0x01;
    // memory[0x01] = 25;
    // memory[0x02] = 0x11;
    // memory[0x03] = 0x01;
    // memory[0x04] = 5;
    // memory[0x05] = 0x14;
    // memory[0x06] = 0xff;
    /***Programm here***/
    load_rom_to_mem(filename, memory);

    CPU cpu(memory);
    if (cpu_debug_flag) {
        cpu.switch_mode();
    }
    cpu.run();

    std::cout << std::endl;
    std::cout << "\tMemory Dump" << std::endl;
    memory.print_hex();

    std::cout << std::endl;
    std::cout << "\tCPU Dump" << std::endl;
    cpu.dump();
    return 0;
}
