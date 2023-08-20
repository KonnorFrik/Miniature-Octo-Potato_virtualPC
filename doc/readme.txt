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
