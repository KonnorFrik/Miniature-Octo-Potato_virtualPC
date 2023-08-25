#include <cmath>
#include <iostream>
#include <string>

#include "cpu.hpp"
#include "memory.hpp"
#include "settings.hpp"
#include "utils.hpp"
#include "architecture.hpp"

#define DEBUG_ARG_WORD "debug"
#define HELP_ARG_WORD "-help"
#define HELP_ARG_WORD_SHORT "-h"
#define BAD_ARGS_CODE 3

void print_help() {
    std::cout << "SAP Emulator" << std::endl;
    std::cout << "Usage:\nsap filename ["
        << DEBUG_ARG_WORD << "] "
        << "[-h | --help]"
        << std::endl;
    std::cout << "filename - required first positional argument" << std::endl;
    std::cout << "debug - optional argument for step mode" << std::endl;
    std::cout << "-h or --help - help message" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filename;
    std::string this_prog_name{argv[0]};
    bool cpu_debug_flag{false};

    if (argc < 2) {
        std::cout << "filename with programm not given" << std::endl;
        print_help();
        exit(BAD_ARGS_CODE);

    } else {
        for (int i = 1; i < argc; ++i) {
            std::string buf{argv[i]};
            if (buf == DEBUG_ARG_WORD) {
                cpu_debug_flag = true;
                continue;
            }

            if (buf == HELP_ARG_WORD || buf == HELP_ARG_WORD_SHORT) {
                print_help();
                exit(0);
                continue;
            }

            if (buf != DEBUG_ARG_WORD && !(buf == HELP_ARG_WORD_SHORT || buf == HELP_ARG_WORD)) {
                filename = buf;
                continue;
            }
        }
    }

    if (DEBUG) {
        std::cout << "[DEBUG]" << std::endl;
        std::cout << "\tthis programm: " << this_prog_name << std::endl;
        std::cout << "\tFilename: " << filename << std::endl;
        std::cout << "\tCpu debug: " << cpu_debug_flag << std::endl;
        std::cout << std::endl;
    }

    int size = pow(2, CPU_BITS);
    Memory memory(size);

    Byte start_addr{0};
    load_rom_to_mem(filename, memory, start_addr);

    CPU cpu(memory, start_addr);
    if (cpu_debug_flag) {
        cpu.switch_mode();
    }
    cpu.set_start_addr(start_addr);
    cpu.run();

    std::cout << std::endl;
    std::cout << "\tMemory Dump" << std::endl;
    memory.print_hex();

    std::cout << std::endl;
    std::cout << "\tCPU Dump" << std::endl;
    cpu.dump();
    return 0;
}
