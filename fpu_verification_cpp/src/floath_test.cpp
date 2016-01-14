/*
 * floath_test.cpp
 *
 *  Created on: 13 Jan 2016
 *      Author: elgf2
 */

/* Test the functionality of the float_h type */

#include "floath.h"
#include "floath_test.h"

/* Generate random float test vectors */
std::vector<float_h> test_vectors(unsigned int n)
{
	/* define max, min */
	float_h min = -1e20;
	float_h max = 1e20;

	/* Init vector of n zeros */
	std::vector<float_h> ret(n, 0.0);

	/* Iterate over vector */
	for (auto &i : ret)
	{
		i = RandomFloat(min, max);
	}

	return ret;
}

float RandomFloat(float_h min, float_h max) {
    float_h random = ((float_h) std::rand()) / (float_h) RAND_MAX;
    float_h diff = max - min;
    float_h r = random * diff;
    return min + r;
}

/* Run float_h add test */
int test_add(const float_h a, const float_h b)
{
	float tmp_a = (float)a;
	float tmp_b = (float)b;

	/* Simulate add */
	float tmp_c = tmp_a + tmp_b;

	/* Run FPU add */
	float_h c = a + b;

	return (tmp_c == c) ? 0 : -1;
}

int test_all(const std::vector<float_h> &vec_a, const std::vector<float_h> &vec_b)
{
	int pass = 0;

	if ( vec_a.size()!= vec_b.size()) {
		return -2;
	}
	unsigned int vec_size = vec_a.size();

	std::vector<float_h> vec_c(vec_size, 0);

	/* Run for all vectors */
	for (std::vector<float_h>::size_type i = 0; i != vec_c.size(); i++)
	{
		/* Test addition */
		pass += test_add(vec_a[i], vec_b[i]);
	}

	return pass;
}
