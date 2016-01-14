/*
 * floath.cpp
 *
 *  Created on: 12 Jan 2016
 *      Author: elgf2
 */

#include "floath.h"

float_h::float_h() {
}

float_h::float_h(float value) {
	// TODO Auto-generated constructor stub
	this->value = value;
}

float_h::~float_h() {
	// TODO Auto-generated destructor stub
}

float_h::operator float() const
{
	return this->value;
}

float_h float_h::operator+(const float_h &a)
{
	return float_h(this->value + a.value);
}

float_h float_h::operator-(const float_h &a)
{
	return float_h(this->value - a.value);
}

float_h float_h::operator*(const float_h &a)
{
	return float_h(this->value * a.value);
}

float_h float_h::operator/(const float_h &a)
{
	return float_h(this->value / a.value);
}

void float_h::operator=(const float_h &a)
{
	this->value = a.value;
}

bool float_h::operator==(const float_h &a)
{
	return ( (float)a.value == this->value) ? true : false;
}

float_h float_h::reciprocal(const float_h &a)
{

}

float_h float_h::log(const float_h &a)
{

}

float_h float_h::sqrt(const float_h &a)
{

}

int float_h::float2int(const float_h &a)
{

}

float_h float_h::int2float(const int &a)
{

}
