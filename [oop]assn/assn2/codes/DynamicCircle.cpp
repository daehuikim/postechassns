#include "DynamicCircle.h"
//dynamicCircle의 member들을 get,set하는 함수들과 초기화부분이다.
DynamicCircle::DynamicCircle()
{
	dynCircleType=0;
	speed_x=0;
	speed_y=0;
	speed_r=0;
}
void DynamicCircle::set_vy(float vy)
{
	speed_y = vy;
}
void DynamicCircle::set_vx(float vx)
{
	speed_x = vx;
}
void DynamicCircle::set_vr(float vr)
{
	speed_r = vr;
}
void DynamicCircle::setType(float aptype)
{
	dynCircleType = aptype;
}
float DynamicCircle::get_vx()
{
	return speed_x;
}
float DynamicCircle::get_vy()
{
	return speed_y;
}
float DynamicCircle::get_vr()
{
	return speed_r;
}