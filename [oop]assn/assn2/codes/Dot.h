#pragma once
#include "Circle.h"
//dot은 circle의 derived class이다.
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