#pragma once
#include "DynamicCircle.h"
//drop�� dynamiccircle�� derived class�̴�.
class DynamicCircle;
class Drop : public DynamicCircle
{
private:
	float gravity;
public:
	Drop();
	void update(Drop* op);
	void set_gravity(float k);
	void set_vyg(Drop* op);
};