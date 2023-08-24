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

    Byte buf;

    switch (this->instruction) {
        case (LD):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - LD, data: "
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << std::endl;
            }

            this->A = buf;
            break;

        case (ADD):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - ADD, data: "
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << std::endl;
            }

            this->A += buf;
            break;

        case (SUB):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - SUB, data: "
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << std::endl;
            }

            this->A -= buf;
            break;

        case (MUL):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - MUL, data: "
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << std::endl;
            }

            this->A *= buf;
            break;

        case (DIV):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - DIV, data: "
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << std::endl;
            }

            this->A /= buf;
            break;

        //case (NEG):
            //buf = load_data();
//
            //if (DEBUG) {
                //std::cout << " - NEG"
                    //<< std::hex
                    //<< static_cast<short>(buf)
                    //<< std::dec
                    //<< std::endl;
            //}
//
            //this->A = -this->A;
            //break;

        case (AND):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - AND, data: "
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << std::endl;
            }

            this->A &= buf;
            break;

        case (OR):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - OR, data: "
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << std::endl;
            }

            this->A |= buf;
            break;

        case (XOR):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - XOR, data: "
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << std::endl;
            }

            this->A ^= buf;
            break;

        case (INV):
            if (DEBUG) {
                std::cout << " - INV" << std::endl;
            }

            this->A = ~this->A;
            break;

        case (HLT):
            if (DEBUG) {
                std::cout << " - HLT" << std::endl;
            }

            this->run_bit = false;
            break;

        default:
            if (DEBUG) {
                std::cout << " - Unknown instruction" << std::endl;
            }

            this->run_bit = false;
            break;
    }
}

CPU::CPU(Memory& memory, Byte start_addr) : memory(memory), start_addr(start_addr) {}

void CPU::run() {
    if (this->mode == STEP) {
        this->memory.print_hex();
        std::cout << std::endl;
    }

    while (this->run_bit) {
        this->instruction = this->memory[this->PC];
        this->PC++;
        execute();

        if (this->mode == STEP) {
            std::cout << std::endl;
            this->dump();
            std::getchar();
        }
    }
}

void CPU::dump() {
    std::cout << "Start Address: " << std::hex << static_cast<short>(this->start_addr) << std::dec << std::endl;
    std::cout << "PC: " << std::hex << static_cast<short>(this->PC) << std::dec << std::endl;
    std::cout << "instruction: " << std::hex << static_cast<short>(this->instruction) << std::dec
              << std::endl;
    std::cout << "run_bit: " << std::hex << this->run_bit << std::dec << std::endl;
    std::cout << "debug mode: " << this->mode << std::endl;
    //std::cout << "data: " << std::hex << static_cast<short>(this->data) << std::dec << std::endl;
    std::cout << "A: hex(" << std::hex << static_cast<short>(this->A) << std::dec << ") dec("
              << static_cast<short>(this->A) << ")" << std::endl;
}

void CPU::set_start_addr(const Byte& addr) {
    this->start_addr = addr;
    this->PC = addr;
}
