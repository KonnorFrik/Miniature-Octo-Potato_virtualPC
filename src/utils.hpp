#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

#include "memory.hpp"

int load_rom_to_mem(const std::string& filename, Memory& mem);

#endif
