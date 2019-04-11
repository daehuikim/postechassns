#pragma once
#include "DynamicCircle.h"
class DynamicCircle;
//ball은 dynamiccircle의 derived class이다.
class Ball : public DynamicCircle
{
private:
	float coeff;
public:
	Ball();
	void update(Ball* op);
	void bounce(Ball* op);
	void set_coeff(float k);
};
