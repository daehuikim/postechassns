#pragma once
#include "Circle.h"
//dot�� circle�� derived class�̴�.
class Circle;
class Dot : public Circle
{
private:
	bool erase;
public:
	Dot();
	void set_erase(float k);
	bool get_erase();
};