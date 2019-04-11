#pragma once
#include "DynamicCircle.h"
class DynamicCircle;
//ballㅐㅐㅜ은 dynamiccircle의 derived class이다.
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