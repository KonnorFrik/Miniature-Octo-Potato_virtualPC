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

CPU::CPU(Memory& memory, Byte start_addr) : memory(memory), start_addr(start_addr) {
    this->PC = start_addr;
}


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
    Byte addr;

    switch (this->instruction) {
        case (LD):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - LD, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A = buf;
            break;

        case (SAV):
            if (DEBUG) {
                std::cout << " - SAV"
                    << std::endl;
            }

            this->DS = this->A;
            break;

        case (SWP):
            if (DEBUG) {
                std::cout << " - SWP"
                    << std::endl;
            }

            buf = this->DS;
            this->DS = this->A;
            this->A = buf;
            break;

        case (ADD):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - ADD, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A += buf;
            break;

        case (SUB):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - SUB, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A -= buf;
            break;

        case (MUL):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - MUL, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A *= buf;
            break;

        case (DIV):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - DIV, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A /= buf;
            break;

        case (AND):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - AND, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A &= buf;
            break;

        case (OR):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - OR, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A |= buf;
            break;

        case (XOR):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - XOR, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
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

        case (LSH):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - LSH, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A <<= buf;
            break;

        case (RSH):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - RSH, data: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A >>= buf;
            break;

        case (JMP):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - JMP, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->PC = buf;
            break;

        case (JEZ):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - JEZ, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            if (this->A == 0) {
                this->PC = buf;
            }
            break;

        case (JNZ):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - JNZ, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            if (this->A != 0) {
                this->PC = buf;
            }
            break;

        case (MEM_INC):
            this->MP += this->A;

            if (DEBUG) {
                std::cout << " - MEM_INC, reg: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(this->MP)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(this->MP)
                    << ")"
                    << std::endl;
            }

            break;

        case (MEM_DEC):
            this->MP -= this->A;

            if (DEBUG) {
                std::cout << " - MEM_DEC, reg: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(this->MP)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(this->MP)
                    << ")"
                    << std::endl;
            }

            break;

        case (MEM_SET):
            this->MP = this->A;

            if (DEBUG) {
                std::cout << " - MEM_SET, reg: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(this->MP)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(this->MP)
                    << ")"
                    << std::endl;
            }

            break;

        case (READ):
            if (DEBUG) {
                std::cout << " - READ, from: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(this->MP)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(this->MP)
                    << ")"
                    << std::endl;
            }

            this->A = this->memory[this->MP];
            break;


        case (WRITE):
            if (DEBUG) {
                std::cout << " - WRITE, to: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(this->MP)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(this->MP)
                    << ")"
                    << std::endl;
            }

            this->memory[this->MP] = this->A;
            break;

        case (HLT):
            if (DEBUG) {
                std::cout << " - HLT" << std::endl;
            }

            this->run_bit = false;
            break;

        case (LD_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - LD_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A = this->memory[buf];
            break;

        case (SAV_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - SAV_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->memory[buf] = this->A;
            break;

        case (SWP_M):
            addr = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - SWP_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(addr)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(addr)
                    << ")"
                    << std::endl;
            }

            buf = this->memory[addr];
            this->memory[addr] = this->A;
            this->A = buf;
            break;

        case (ADD_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - ADD_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A += this->memory[buf];
            break;

        case (SUB_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - SUB_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A -= this->memory[buf];
            break;

        case (MUL_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - MUL_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A *= this->memory[buf];
            break;

        case (DIV_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - DIV_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A /= this->memory[buf];
            break;

        case (AND_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - AND_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A &= this->memory[buf];
            break;

        case (OR_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - OR_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A |= this->memory[buf];
            break;

        case (XOR_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - XOR_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A ^= this->memory[buf];
            break;

        case (LSH_M):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - LSH_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A <<= this->memory[buf];
            break;

        case (RSH_M):
            buf = load_data();

            if (DEBUG) {
                std::cout << " - RSH_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->A >>= this->memory[buf];
            break;

        case (JMP_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - JMP_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            this->PC = this->memory[buf];
            break;

        case (JEZ_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - JEZ_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            if (this->A == 0) {
                this->PC = this->memory[buf];
            }
            break;

        case (JNZ_M):
            buf = load_data() + this->start_addr;

            if (DEBUG) {
                std::cout << " - JNZ_M, addr: "
                    << "hex("
                    << std::hex
                    << static_cast<short>(buf)
                    << std::dec
                    << "), dec("
                    << static_cast<short>(buf)
                    << ")"
                    << std::endl;
            }

            if (this->A != 0) {
                this->PC = this->memory[buf];
            }
            break;

        default:
            if (DEBUG) {
                std::cout << " - Unknown instruction" << std::endl;
            }

            this->run_bit = false;
            break;
    }
}

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
    std::cout << "Start Address: "
        << std::hex << static_cast<short>(this->start_addr)
        << std::dec << std::endl;

    std::cout << "run_bit: " << this->run_bit << std::endl;
    std::cout << "debug mode: " << this->mode << std::endl;

    std::cout << "PC: "
        << std::hex << static_cast<short>(this->PC)
        << std::dec << std::endl;

    std::cout << "instruction: "
        << std::hex << static_cast<short>(this->instruction)
        << std::dec << std::endl;

    std::cout << "MP: hex("
        << std::hex << static_cast<short>(this->MP)
        << std::dec << ") dec(" << static_cast<short>(this->MP)
        << ")" << std::endl;

    std::cout << "DS: hex("
        << std::hex << static_cast<short>(this->DS)
        << std::dec << ") dec(" << static_cast<short>(this->DS)
        << ")" << std::endl;

    std::cout << "A: hex("
        << std::hex << static_cast<short>(this->A)
        << std::dec << ") dec(" << static_cast<short>(this->A)
        << ")" << std::endl;
}

//void CPU::set_start_addr(const Byte& addr) {
    //this->start_addr = addr;
    //this->PC = addr;
//}
