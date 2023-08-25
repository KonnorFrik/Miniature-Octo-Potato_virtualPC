#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__

using Byte = unsigned char;
using Word = unsigned short;

// Instructions for cpu
static const Byte LD = 0x01;   // load data
static const Byte SAV = 0x02;   // save A to DS
static const Byte SWP = 0x03;   // swap A and DS
                               //
static const Byte ADD = 0x11;  // +
static const Byte SUB = 0x12;  // -
static const Byte MUL = 0x13;  // *
static const Byte DIV = 0x14;  // /
//static const Byte NEG = 0x15;  // /

static const Byte AND = 0x20;  // &
static const Byte OR = 0x21;   // |
static const Byte XOR = 0x22;  // ^
static const Byte INV = 0x23;  // ~

static const Byte JMP = 0x30;
static const Byte JEZ = 0x31;
static const Byte JNZ = 0x32;

static const Byte HLT = 0xff;

#endif
