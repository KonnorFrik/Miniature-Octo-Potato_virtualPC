#include "cpu.hpp"

#include <iostream>

#include "memory.hpp"
#include "settings.hpp"

/*
 * 8 bit cpu
 * all registers is - 8 bit = 1 byte
 * one intstruction - 8 bit
 * one data         - 8 bit
 */

Byte CPU::load_data() {
    Byte res = this->memory[this->PC];
    this->PC++;
    return res;
}

void CPU::switch_mode() {
    if (this->mode == MAIN) {
        this->mode = STEP;

    } else {
        this->mode = MAIN;
    }
}

void CPU::execute() {
    if (DEBUG) {
        std::cout << "[DEBUG] Istruction: " << std::hex << static_cast<short>(this->instruction) << std::dec;
    }

    switch (this->instruction) {
        case (LD):
            this->data = load_data();
            if (DEBUG) {
                std::cout << " - LD "
                          << "data: " << std::hex << static_cast<short>(this->data) << std::dec << std::endl;
            }
            break;

        case (ADD):
            if (DEBUG) {
                std::cout << " - ADD" << std::endl;
            }
            this->A += this->data;
            break;

        case (SUB):
            if (DEBUG) {
                std::cout << " - SUB" << std::endl;
            }
            this->A -= this->data;
            break;

        case (MUL):
            if (DEBUG) {
                std::cout << " - MUL" << std::endl;
            }
            this->A *= this->data;
            break;

        case (DIV):
            if (DEBUG) {
                std::cout << " - DIV" << std::endl;
            }
            this->A /= this->data;
            break;

        case (HLT):
            if (DEBUG) {
                std::cout << " - HLT" << std::endl;
            }
            this->run_bit = false;
            break;

        default:
            std::cout << " - Unknown instruction" << std::endl;
            this->run_bit = false;
            break;
    }
}

CPU::CPU(Memory& memory) : memory(memory) {}

void CPU::run() {
    if (this->mode) {
        this->memory.print_hex();
        std::cout << std::endl;
    }

    while (this->run_bit) {
        this->instruction = this->memory[this->PC];
        this->PC++;
        execute();

        if (this->mode) {
            std::cout << std::endl;
            this->dump();
            std::getchar();
        }
    }
}

void CPU::dump() {
    std::cout << "PC: " << std::hex << static_cast<short>(this->PC) << std::dec << std::endl;
    std::cout << "instruction: " << std::hex << static_cast<short>(this->instruction) << std::dec
              << std::endl;
    std::cout << "run_bit: " << std::hex << this->run_bit << std::dec << std::endl;
    std::cout << "debug mode: " << this->mode << std::endl;
    std::cout << "data: " << std::hex << static_cast<short>(this->data) << std::dec << std::endl;
    std::cout << "A: hex(" << std::hex << static_cast<short>(this->A) << std::dec << ") dec("
              << static_cast<short>(this->A) << ")" << std::endl;
}
