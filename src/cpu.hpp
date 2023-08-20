#ifndef __CPU_H__
#define __CPU_H__

#include "architecture.hpp"
#include "memory.hpp"

#define CPU_BITS 8
enum RUN_MODE {
    MAIN = 0,
    STEP,
};

class CPU {
    Memory& memory;

    Byte PC{0};           // mem addr
    Byte instruction{0};  // for store instruction
    //Byte data{0};         // for store data
    Byte A{0};            // number register (like output register)
    bool run_bit{true};

    Byte load_data();
    void execute();

    short mode{MAIN};

   public:
    explicit CPU(Memory&);

    void run();
    void dump();
    void switch_mode();
};

#endif
