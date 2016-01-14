/*
 * registers.h
 *
 *  Created on: 14 Jan 2016
 *      Author: elgf2
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

/* Define Base Register offset */
#define BASE_REGISTER 0x0

/* Define registers */
#define INSTRUCTION 0x0
#define DATA 0x20

/* Internal Registers */
#define R0 0x0
#define R1 0x1
#define R2 0x2
#define R3 0x3
#define R4 0x4
#define R5 0x5
#define R6 0x6
#define R7 0x7
#define R8 0x8
#define R9 0x9
#define R10 0xa
#define R11 0xb
#define R12 0xc
#define R13 0xd
#define R14 0xe
#define R15 0xf
#define R16 0x10
#define R17 0x11
#define R18 0x12
#define R19 0x13
#define R20 0x14
#define R21 0x15
#define R22 0x16
#define R23 0x17
#define R24 0x18
#define R25 0x19
#define R26 0x1a
#define R27 0x1b
#define R28 0x1c
#define R29 0x1d
#define R30 0x1e
#define R31 0x1f

/* Define Instructions */
#define NOP 	0x0
#define FADD	0x1
#define FSUB 	0x2
#define FMUL	0x3
#define FDIV	0x4
#define FF2I	0x5
#define FI2F	0x6
#define FABS 	0x7
#define FSQT	0x8
#define	FLOG	0x9
#define FREC	0xa
#define FMOV	0x10

/* Bitmasks */
#define instruction_mask	0x000000ff
#define ra_mask 			0x0000ff
#define rb_mask 			0x00ff
#define rc_mask 			0xff

/* Register storage structure */
struct reg{
	float value;
	bool available;
};

#endif /* REGISTERS_H_ */
