/*
 * floath_test.h
 *
 *  Created on: 13 Jan 2016
 *      Author: elgf2
 */

#ifndef FLOATH_TEST_H_
#define FLOATH_TEST_H_

#include <vector>
#include <cstdlib>

std::vector<float_h> test_vectors(unsigned int n);

float RandomFloat(float_h a, float_h b);

int test_all(const std::vector<float_h> &vec_a, const std::vector<float_h> &vec_b);

/* Test Procedures */
int test_add(const float_h a, const float_h b);

#endif /* FLOATH_TEST_H_ */
