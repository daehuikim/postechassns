#pragma once
#include "DynamicCircle.h"
class DynamicCircle;
//ball�������� dynamiccircle�� derived class�̴�.
class Balloon : public DynamicCircle
{
private:
	bool popping;
public:
	Balloon();
	void update(Balloon* op);
	void pop(Balloon* op);
	void set_popping(int k);
	bool get_popping();
};