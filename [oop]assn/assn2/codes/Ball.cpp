#include "Ball.h"
//ball에 대한 기본 member변수들의 초기화와 set함수
Ball::Ball()
{
	coeff = 0;
}
void Ball::update(Ball* op)//(여기서도 x, y가 뒤바껴서 표현을 이렇게 했습니다.)
{
	float t = op->get_x();//튕겨나온 후 위치를 조정하는 것인데, 각각 x,y값에 대한 상호 계산과정이 있어서 이렇게 얕은복사 후 값을 지정
	op->set_y(op->get_y() + op->get_vx());
	op->set_x(t + op->get_vy());
}
void Ball::bounce(Ball* op)
{
	op->set_vy(-1 * coeff*op->get_vy());//공식대로 튕겨나온 후의 속도를 지정
	op->set_vx(-1 * coeff*op->get_vx());
}
void Ball::set_coeff(float k)
{
	coeff = k;
}