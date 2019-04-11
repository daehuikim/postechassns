#include "Drop.h"
//drop�� ������� �ʱ�ȭ�� get set�κ��̴�.
Drop::Drop()
{
	gravity=0;
}
void Drop::update(Drop* op)
{
	op->set_x(op->get_x() - op->get_vy() - gravity/2.0);//update�ÿ� �׻� y=v-2/g ������ Ȱ��(���⼭�� x,y�� �ڹٲ��� ǥ���� �̷��� �߽��ϴ�.)
	op->set_vyg(op);//vy�� g�� ���� �ٲ��� ǥ��
}
void Drop::set_gravity(float k)
{
	gravity = k;
}
void Drop::set_vyg(Drop* op)
{
	op->set_vy(op->get_vy() + gravity);
}