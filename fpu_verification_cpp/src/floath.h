/*
 * floath.h
 *
 *  Created on: 12 Jan 2016
 *      Author: elgf2
 */

#ifndef FLOATH_H_
#define FLOATH_H_

class float_h
{
public:
	float_h();
	float_h(float value);
	virtual ~float_h();

	/* Casting operator */
	operator float() const;

	/* Overload arithmetic operators */
	float_h operator+(const float_h &a);
	float_h operator-(const float_h &a);
	float_h operator*(const float_h &a);
	float_h operator/(const float_h &a);

	/* Equality/assignment operators */
	void operator=(const float_h &a);
	bool operator==(const float_h &a);

	/* Other operators */
	float_h reciprocal(const float_h &a);
	float_h log(const float_h &a);
	float_h sqrt(const float_h &a);
	int float2int(const float_h &a);
	float_h int2float(const int &a);

private:
	float value;
};

#endif /* FLOATH_H_ */
