#pragma once
#include "DynamicCircle.h"
class DynamicCircle;
//ball�� dynamiccircle�� derived class�̴�.
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
