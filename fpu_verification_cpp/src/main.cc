/*
 * Empty C++ Application
 */

#include <stdio.h>

#include <xil_printf.h>
#include "platform/platform.h"

#include <vector>

#include "fpu/fpu.h"

#include "floath.h"
#include "floath_test.h"


#include <xil_io.h>

int main()
{
	int status = 0;

	init_platform();

	xil_printf("Platform Initialised \r\n");

	unsigned int var = 0xffffffff;
	unsigned int cmd = 0;

	Xil_Out32(0x43C00000+ (32*4), 0x0badf00d);
	do {
		var = Xil_In32(0x43C00000);
	}
	while (var == 0xffffffff);
	var = Xil_In32(0x43C00000);
	xil_printf("%x \r\n", cmd);

	for (int i=R0; i<=R31; i++)
	{
		cmd = 0x10000000 | i << 16;
		Xil_Out32(0x43C00000, cmd);
		do {
			var = Xil_In32(0x43C00000);
		}
		while (var == 0xffffffff);
	}
	for (int i=R0; i<=R31+1; i++)
	{
		var = Xil_In32(0x43C00000+ (i*4));
		xil_printf("R%d: %x \r\n", i, var);
	}

	/* Test FPU */
	/*xil_printf("Handshaking FPU \r\n");
	fpu fpu_0;
	int success = fpu_0.handshake();
	xil_printf("FPU says: %d \r\n", success);

	float_h res;
	success = fpu_0.add(0.1, 0.2, res);
	xil_printf("c: %f \r\n", (float)res);
	*/
	/*
	std::vector<float_h> vector_a;
	std::vector<float_h> vector_b;

	vector_a = test_vectors(100);
	vector_b = test_vectors(100);

	status = test_all(vector_a, vector_b);
	xil_printf("%d", status);
	*/

	cleanup_platform();

	return status;
}
