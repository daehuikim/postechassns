#include "DynamicCircle.h"
//dynamicCircle�� member���� get,set�ϴ� �Լ���� �ʱ�ȭ�κ��̴�.
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