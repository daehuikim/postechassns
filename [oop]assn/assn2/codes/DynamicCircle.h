#pragma once
#include "Circle.h"
class Circle;
//dynamiccircle은 circle의 derived class이다.
class DynamicCircle :public Circle
{
private:
	int dynCircleType;
	float speed_x;
	float speed_y;
	float speed_r;
public:
	DynamicCircle();
	void set_vy(float vy);
	void set_vx(float vx);
	void set_vr(float vr);
	void setType(float aptype);
	float get_vx();
	float get_vy();
	float get_vr();
};