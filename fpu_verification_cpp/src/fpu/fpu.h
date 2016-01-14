/*
 * fpu.h
 *
 *  Created on: 12 Jan 2016
 *      Author: elgf2
 */

#ifndef FPU_H_
#define FPU_H_

#include "../floath.h"
#include "registers.h"
#include "xparameters.h"

#include <xil_printf.h>

/* Class represents software abstraction of hardware FPU */
class fpu {
public:
	fpu();
	virtual ~fpu();

	int handshake();

	int add(const float_h &a, const float_h &b, float_h &c);

private:
	unsigned int base_ptr = XPAR_FPU_AXI4LITE_SLAVE_0_AXI4LITE_SLAVE_REGSIF_0_BASEADDR;
	struct reg registers[32];

	/* Build instruction code */
	unsigned int instruction(unsigned int opcode, unsigned int ra, unsigned int rb, unsigned int rc);

	/* Write to register */
	float_h read_reg(unsigned int reg);
	void write_reg(unsigned int reg, float_h value);

	/* Transaction operations */
	int read_float(unsigned int reg, float_h &value);
	int write_float(unsigned int reg, const float_h &value);

	/* DO NOT use these methods if you don't know what you're doing.*/
	unsigned int read_raw(unsigned int reg);
	void write_raw(unsigned int reg, unsigned int value);

	/* Allocate a register */
	int alloc_reg(unsigned int rx);

	/* Deallocate a register */
	int dealloc_reg(unsigned int rx);

	/* Local copy operations */
	int swap_registers(unsigned int ra, unsigned int rb);

	/* Find empty register; returns empty register or -1 if fail */
	int find_empty_register();
};

#endif /* FPU_H_ */
