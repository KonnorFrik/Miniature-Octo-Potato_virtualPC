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

    Byte start_addr{0};
    Byte PC{0};           // mem addr
    Byte instruction{0};  // for store instruction
    //Byte data{0};         // for store data
    Byte A{0};            // number register (like output register)
    Byte DS{0};             // data storage reg
    bool run_bit{true};

    Byte load_data();
    void execute();

    short mode{MAIN};

   public:
    explicit CPU(Memory&, Byte);

    void run();
    void dump();
    void switch_mode();
    void set_start_addr(const Byte&);
};

#endif
