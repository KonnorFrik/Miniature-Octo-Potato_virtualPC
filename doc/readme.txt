    Emulating of some CPU
It is emulator of SAP (simple as possible) architecture

Emulator:
    -read given ROM with compiled programm in self memory
    -start executing programm until the halt instruction is executed
    -print self state and memory to stdout
    -stop work when execute 'halt' instruction or read '0x00' byte as instruciton
    Usage:
        ./sap filename

Compiler:
    -read input text programm, compile it and write to output file
    -use binary tree for processing tokens
    Usage:
        python path/to/compiler.py filename_input filename_output

Editor:
    Simple terminal editor
    for more info use '@help' in editor
    Usage:
        python editor.py [-s | --size <num>] | [-b | --binary]

Architecture:
    CPU:
        registers:
            A(accumulator): 8-bit - all math operations results store here
            --data: 8-bit - for store loaded data from memory for operations
            PC aka Instruction pointer: 8-bit - store address of next instruction in memory
            instruction: 8-bit - store current instruction for execution
            run_bit: 1-bit
    Memory:
        8-bit for one cell


