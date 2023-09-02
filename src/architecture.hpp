#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__

using Byte = unsigned char;
using Word = unsigned short;

// Instructions for cpu
static const Byte LD = 0x01;   // load data
static const Byte SAV = 0x02;   // save A to DS
static const Byte SWP = 0x03;   // swap A and DS

static const Byte LD_M = 0x04;   // load data from mem
static const Byte SAV_M = 0x05;   // save A to mem
static const Byte SWP_M = 0x06;   // swap A and mem

static const Byte ADD = 0x11;  // A = A + num
static const Byte SUB = 0x12;  // A = A - num
static const Byte MUL = 0x13;  // A = A * num
static const Byte DIV = 0x14;  // A = A / num

static const Byte ADD_M = 0x15;  // A = A + mem
static const Byte SUB_M = 0x16;  // A = A - mem
static const Byte MUL_M = 0x17;  // A = A * mem
static const Byte DIV_M = 0x18;  // A = A / mem

static const Byte AND = 0x20;  // A = A & num
static const Byte OR = 0x21;   // A = A | num
static const Byte XOR = 0x22;  // A = A ^ num
static const Byte INV = 0x23;  // A = ~A

static const Byte AND_M = 0x24;  // A = A & mem
static const Byte OR_M = 0x25;   // A = A | mem
static const Byte XOR_M = 0x26;  // A = A ^ mem

static const Byte JMP = 0x30;
static const Byte JEZ = 0x31;
static const Byte JNZ = 0x32;

static const Byte JMP_M = 0x33;
static const Byte JEZ_M = 0x34;
static const Byte JNZ_M = 0x35;

static const Byte HLT = 0xff;


static const int HEADER_SIZE = 16;

#endif
