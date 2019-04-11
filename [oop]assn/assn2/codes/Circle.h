#pragma once
#include <iostream>
//circle은 dot과 dynamicCircle의 base class이다.
class Circle{
private:
	float radius;
	float center_x;
	float center_y;
	float color[4];
	int type;
	bool dynamicity;
	int i;//int i 는 color배열에 index에 접근하기 위한 변수선언이다.
	float k;
public:
	Circle();
	void set_x(float x);
	void set_y(float y);
	void set_ra(float ra);
	void set_type(int type);
	void set_dynamicity();
	void set_color(float data);
	float get_R();
	float get_G();
	float get_B();
	float get_A();
	float get_x();
	float get_y();
	float get_rad();
	int get_type();
	float get_k();
	void set_k(float ink);
};