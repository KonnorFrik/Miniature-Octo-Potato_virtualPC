#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "architecture.hpp"

class Memory {
    Byte* memory{nullptr};
    int size{0};
    short cols_per_row{16};

    void print_row(const int);

   public:
    explicit Memory(const int);
    explicit Memory(Memory&);
    ~Memory();

    void nullify();
    void fill(Byte);
    void print_raw();
    void print_hex();

    Byte& operator[](const int);
};

#endif
