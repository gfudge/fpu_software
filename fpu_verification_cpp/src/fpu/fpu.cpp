/*
 * fpu.cpp
 *
 *  Created on: 12 Jan 2016
 *      Author: elgf2
 */

#include "fpu.h"

fpu::fpu() {
	// TODO Auto-generated constructor stub

}

fpu::~fpu() {
	// TODO Auto-generated destructor stub
}

int fpu::handshake()
{
	int success = 0;
	unsigned int data = 0xdeadbeef;
	unsigned int result = 0x0badf00d;

	/* Perform read and write of each register */
	for (unsigned int r=R0; r < R31; r++)
	{
		this->write_raw(r, data+r);
		result = this->read_raw(r);
		/* If success, increment
		 * if error, decrement by 100
		 * if all pass, success = 31
		 */
		success += (data == result) ? 1 : -100;
	}

	for (unsigned int r=R0; r < 31; r++)
	{
		result = this->read_raw(r);
		xil_printf("R%d = %x \r\n", r, result);
	}

	return success;
}

int fpu::add(const float_h &a, const float_h &b, float_h &c)
{
	int status = 0;
	/* Find 3 registers */
	unsigned int ra = this->find_empty_register();
	unsigned int rb = this->find_empty_register();
	unsigned int rc = this->find_empty_register();

	/* Get instruction code */
	unsigned int cmd = this->instruction(FADD, ra, rb, rc);

	/* Write registers */
	this->write_reg(ra, a);
	this->write_reg(rb, b);
	//this->write_reg(rc, c);

	this->write_raw(INSTRUCTION, cmd);

	c = this->read_reg(rc);

	return status;
}

unsigned int fpu::instruction(unsigned int opcode, unsigned int ra, unsigned int rb, unsigned int rc)
{
	/* Check instruction */
	if (opcode < NOP || opcode > FREC) {
		return -1;
	}

	/* Check all register values */
	if (ra < R0 || ra > R31) {
		return -2;
	}
	if (rb < R0 || rb > R31) {
		return -3;
	}
	if (rc < R0 || rc > R31) {
		return -2;
	}

	unsigned int instruction = 0;

	/* Copy opcode */
	instruction |= instruction_mask & (opcode << 24);
	instruction |= ra_mask & (ra << 16);
	instruction |= rb_mask & (rb << 8);
	instruction |= rc_mask & (rc << 0);

	return instruction;
}

/* Read back register into host side copy */
float_h fpu::read_reg(unsigned int reg)
{
	if (reg < R0 || reg > R31) {
		return 0.0;
	}

	/* If register not allocated, allocate it now */
	if (registers[reg].available) {
		alloc_reg(reg);
	}

	/* Sync the values of register */
	float_h tmp_val = 0.0;
	int success = this->read_float(reg, tmp_val);
	registers[reg].value = tmp_val;
	return (success) ? registers[reg].value : -1;
}

/* Write a value into a register on FPU */
void fpu::write_reg(unsigned int reg, float_h value)
{
	/* Allocate a register and write value to DATA on fpu */
	int status = this->alloc_reg(reg);
	registers[reg].value = value;
	status |= this->write_float(DATA, registers[reg].value);

	/* Generate the instruction to copy the data into register */
	unsigned int mov = this->instruction(FMOV, reg, 0, 0);
	this->write_raw(INSTRUCTION, mov);
}

int fpu::read_float(unsigned int reg, float_h &data)
{
	int status = -1;
	/* Check range of register */
	if (reg < 0 || reg > 31) {
		/* Error, return negative */
		return -2;
	}
	/* Attempt to read register */
	data = *(volatile unsigned int*)( this->base_ptr + (reg * 4) );

	/*
	if (value != nullptr) {
		return value;
	}
	else {
		return -1;
	}*/
	return status;
}

int fpu::write_float(unsigned int reg, const float_h &data)
{
	int status = -1;
	/* Check range of register */
	if (reg < 0 || reg > 31) {
		return -2;
	}
	/*Attempt to write register */
	*(volatile unsigned int*)(this->base_ptr + (reg * 4)) = (float)data;

	/*
	if (*value != nullptr){
		return 0;
	}
	else {
		return -1;
	}*/
	return status;
}

/* Raw read and write operations */
unsigned int fpu::read_raw(unsigned int reg)
{
	unsigned int value;
	/* Check register bounds */
	if(reg < R0 || reg > R31)
	{
		return -1;
	}
	value = *(volatile int*)( this->base_ptr + (reg * 4) );
	return value;
}

void fpu::write_raw(unsigned int reg, unsigned int value)
{
	/* Check register bounds */
	if(reg < R0 || reg > R31) {
		return;
	}
	*(volatile int*)(this->base_ptr + (reg * 4)) = value;
	return;
}

/* Allocate register */
int fpu::alloc_reg(unsigned int rx)
{
	int status = -1;
	if(rx < R0 || rx > R31) {
		return status;
	}
	if ( registers[rx].available ) {
		registers[rx].value = 0.0;
		registers[rx].available = false;
	}
	return (registers[rx].available == false) ? 0 : -1;
}

/* Deallocate register */
int fpu::dealloc_reg(unsigned int rx)
{
	int status = -1;
	if(rx < R0 || rx > R31)
	{
		return status;
	}
	if (!registers[rx].available) {
		registers[rx].value = 0.0;
		registers[rx].available = false;
	}
	return (registers[rx].available == true) ? 0 : -1;
}

int fpu::swap_registers(unsigned int ra, unsigned int rb)
{
	/* Check register are in bounds */
	if ( ra < 0 || ra > 31 )
	{
		return -1;
	}
	if ( rb < 0 || rb > 31 )
	{
		return -2;
	}

	struct reg tmp_reg = registers[ra];
	registers[ra] = registers[rb];
	registers[rb] = tmp_reg;
	return 0;
}

/* Return the first unoccupied register */
int fpu::find_empty_register()
{
	for(int r=R0; r<R31; r++)
	{
		if(registers[r].available == true)
		{
			return r;
		}
	}
	/* If no registers available, return -1 */
	return -1;
}
