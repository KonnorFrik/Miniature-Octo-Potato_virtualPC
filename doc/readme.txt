|===================================Virtual CPU=================================================|
|                    Based on sap (simple as possible) architecture                             |
|===============================================================================================|
|                                     Install                                                   |
|Compiled programm will be in the 'bin' folder                                                  |
|Usage:                                                                                         |
|   make install                                                                                |
|===============================================================================================|
|                                  Architecture                                                 |
|CPU:                                                                                           |
|    registers:                                                                                 |
|        A(accumulator): 8-bit - all math and bitwise operations results store here             |
|        DC: 8-bit - for store data from register A. Can't be writed or readed directly         |
|        PC aka Instruction pointer: 8-bit - store address of next instruction in memory        |
|Memory:                                                                                        |
|    8-bit for one cell                                                                         |
|===============================================================================================|
|                                    Emulator                                                   |
|    -read given ROM with compiled programm in self memory                                      |
|    -start executing programm until the halt instruction is executed or find '0x00             |
|    -print self state and memory state to stdout                                               |
|Usage:                                                                                         |
|    ./sap filename                                                                             |
|===============================================================================================|
|                                    Compiler                                                   |
|    -read input text programm, compile it and write to output file                             |
|    -can compile numbers without instruction, like it is data                                  |
|Usage:                                                                                         |
|    python path/to/compiler.py filename_input filename_output                                  |
|===============================================================================================|
|                                     Editor                                                    |
|Simple terminal editor                                                                         |
|for more info use '@help' in editor                                                            |
|Usage:                                                                                         |
|    python editor.py [-s | --size <num>] | [-b | --binary]                                     |
|===============================================================================================|
|                                    Language                                                   |
|                                   &                                                           |
|                                    Instructions                                               |
| [KEYWORD] [NUMBER]                                                                            |
|                                                                                               |
|Keywords:                                                                                      |
|   ld [num] - load 'num' to A register                                                         | 
|   sav - save data from A register to DS                                                       |
|   swp - swap data in A and DS registers                                                       |
|                                                                                               |
|   add [num] - result of sum of 'num' and data in A put in A                                   |
|   sub [num] - result of subtract of 'num' and data in A put in A                              |
|   mul [num] - result of multiplication of 'num' and data in A put in A                        |
|   div [num] - result of division of 'num' and data in A put in A                              |
|                                                                                               |
|   and [num] - result of bitswise AND of 'num' and data in A put in A                          |
|   or [num] - result of bitswise OR of 'num' and data in A put in A                            |
|   xor [num] - result of bitswise XOR of 'num' and data in A put in A                          |
|   inv - bitswise INVERT A register                                                            |
|                                                                                               |
|   jmp [num] - jump to addr 'num'                                                              |
|   jez [num] - jump to addr 'num' if A = 0                                                     |
|   jnz [num] - jump to addr 'num' if A not = 0                                                 |
|   hlt - halt, set 'run bit' to 0/false and exit                                               |
|                                                                                               |
|Number:                                                                                        |
|   any number between 0 and 255 in decimal or hexadecimal format                               |
|===============================================================================================|
