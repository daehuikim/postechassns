#include "Balloon.h"
//balloon member�� ���� ��� �ʱ�ȭ�� get,set�κ��� ��� �ִ�.
Balloon::Balloon ()
{
	popping=0;
}
void Balloon::update(Balloon* op)
{
	op->set_ra(op->get_rad() + op->get_vr());//vr�� ���Ͽ� r�� �þ�� �κ��� ��Ÿ�´�.
}
void Balloon::pop(Balloon* op)
{
	op->set_ra(0);//���� pop�ϰ� �ȴٸ� vr�� radius�� ���� 0���� ���� ǳ���� ������ �Ѵ�.
	op->set_vr(0);
}
void Balloon::set_popping(int k)
{
	popping = k;
}
bool Balloon::get_popping()
{
	return popping;
}