#include "Ball.h"
//ball�� ���� �⺻ member�������� �ʱ�ȭ�� set�Լ�
Ball::Ball()
{
	coeff = 0;
}
void Ball::update(Ball* op)//(���⼭�� x, y�� �ڹٲ��� ǥ���� �̷��� �߽��ϴ�.)
{
	float t = op->get_x();//ƨ�ܳ��� �� ��ġ�� �����ϴ� ���ε�, ���� x,y���� ���� ��ȣ �������� �־ �̷��� �������� �� ���� ����
	op->set_y(op->get_y() + op->get_vx());
	op->set_x(t + op->get_vy());
}
void Ball::bounce(Ball* op)
{
	op->set_vy(-1 * coeff*op->get_vy());//���Ĵ�� ƨ�ܳ��� ���� �ӵ��� ����
	op->set_vx(-1 * coeff*op->get_vx());
}
void Ball::set_coeff(float k)
{
	coeff = k;
}