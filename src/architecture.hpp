#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__

using Byte = unsigned char;
using Word = unsigned short;

// Instructions for cpu
static const Byte LD = 0x01;   // load data
                               //
static const Byte ADD = 0x11;  // +
static const Byte SUB = 0x12;  // -
static const Byte MUL = 0x13;  // *
static const Byte DIV = 0x14;  // /

static const Byte AND = 0x20;  // &

static const Byte HLT = 0xff;

#endif
