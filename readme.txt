|===================================Virtual CPU=================================================|
|                    Based on sap (simple as possible) architecture                             |
|===============================================================================================|
|                                     Install                                                   |
|Compiled programm will be in the 'bin' folder                                                  |
|Usage:                                                                                         |
|   make                                                                                        |
|===============================================================================================|
|                                  Architecture                                                 |
|CPU:                                                                                           |
|    registers:                                                                                 |
|        A(accumulator): 8-bit - all math and bitwise operations results store here             |
|        DS: 8-bit - for store data from register A. Can't be writed or readed directly         |
|        PC (Programm Counter): 8-bit - store address of next instruction in memory             |
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
|    python editor.py [-s | --size <num>] | [-b | --binary] | [-h]                              |
|===============================================================================================|
|                                    Language                                                   |
|                                   &                                                           |
|                                    Instructions                                               |
| [KEYWORD] [OPERATOR] [NUMBER | ADDRESS]                                                       |
|                                                                                               |
|Keywords:                                                                                      |
|   all in square brackets are optional                                                         |
|                                                                                               |
|   ao - access operator                                                                        |
|                                                                                               |
|   ld  [ao] [num | addr] - load 'num' to A register                                            | 
|   sav [ao] [num | addr] - save data from A register to DS                                     |
|   swp [ao] [num | addr] - swap data in A and DS registers                                     |
|                                                                                               |
|   add [ao] [num | addr] - result of sum of 'num' and data in A put in A                       |
|   sub [ao] [num | addr] - result of subtract of 'num' and data in A put in A                  |
|   mul [ao] [num | addr] - result of multiplication of 'num' and data in A put in A            |
|   div [ao] [num | addr] - result of division of 'num' and data in A put in A                  |
|                                                                                               |
|   and [ao] [num | addr] - result of bitswise AND of 'num' and data in A put in A              |
|   or  [ao] [num | addr] - result of bitswise OR of 'num' and data in A put in A               |
|   xor [ao] [num | addr] - result of bitswise XOR of 'num' and data in A put in A              |
|   inv                   - bitswise INVERT A register                                          |
|   lsh [ao] [num | addr] - bitwise shifting the A register to left                             |
|   rsh [ao] [num | addr] - bitwise shifting the A register to right                            |
|                                                                                               |
|   jmp [ao] [addr]       - jump to addr 'num'                                                  |
|   jez [ao] [addr]       - jump to addr 'num' if A = 0                                         |
|   jnz [ao] [addr]       - jump to addr 'num' if A not = 0                                     |
|   hlt                   - halt, set 'run bit' to 0/false and exit                             |
|                                                                                               |
|Number and Address:                                                                            |
|   any number between 0 and 255 in decimal or hexadecimal format                               |
|                                                                                               |
|Operators:                                                                                     |
|   $ - Memory access operator                                                                  |
|       Provides access to a memory location to read/write values                               |
|       Used with: ld, sav, swp, add, sub, mul, div, and, or, xor, jmp, jez, jnz                |
|       Exmp: "ld $n" - load to register A value from memory cell with address 'n'              |
|===============================================================================================|
|                                  Memory Addressing                                            |
|Emulator have relative memory addressing. That mean if in your programm writed "jmp 0x01" and  |
|   in header of programm 'start offset' is '0x02' the real address for intstruction will be    |
|   'address + offset' (0x01 + 0x02)                                                            |
|===============================================================================================|
|                                       Notes                                                   |
|   - Compiler can compile a number without instruction                                         |
|       Can be used as static data in programm                                                  |
|       Be carefully with numbers in middle of the programm                                     |
|===============================================================================================|
