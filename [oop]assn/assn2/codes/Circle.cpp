#include "Circle.h"
#include <iostream>
using namespace std;
//circle member�� ���� �ʱ�ȭ�� getset�� ��� �ִ�.
Circle::Circle()
{
	dynamicity=0;
	i = 0; //color��� �迭�� ����(RGBA)�� ������� ��� ���ؼ� indexȰ���� ���� int i�� ���� �� 0���� �ʱ�ȭ�Ѵ�.
}
void Circle::set_x(float x)
{
	center_x = x;
}
void Circle::set_y(float y)
{
	center_y = y;
}
void Circle::set_ra(float ra)
{
	radius = ra;
}
void Circle::set_type(int aptype)
{
	type = aptype;
}
void Circle::set_dynamicity()
{
	if (type == 0)
		dynamicity = 0;
	if (type != 0)
		dynamicity = 1;
}
void Circle::set_color(float data)
{
	color[i] = data;
	i++;
}
float Circle::get_R()
{
	return color[0];
}
float Circle::get_G()
{
	return color[1];
}
float Circle::get_B()
{
	return color[2];
}
float Circle::get_A()
{
	return color[3];
}
float Circle::get_x()
{
	return center_x;
}
float Circle::get_y()
{
	return center_y;
}
float Circle::get_rad()
{
	return radius;
}
int Circle::get_type()
{
	return type;
}
float Circle::get_k()
{
	return k;
}
void Circle::set_k(float ink)
{
	k = ink;
}