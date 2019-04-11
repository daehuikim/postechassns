#include "Drop.h"
//drop의 멤버변수 초기화와 get set부분이다.
Drop::Drop()
{
	gravity=0;
}
void Drop::update(Drop* op)
{
	op->set_x(op->get_x() - op->get_vy() - gravity/2.0);//update시에 항상 y=v-2/g 공식을 활용(여기서도 x,y가 뒤바껴서 표현을 이렇게 했습니다.)
	op->set_vyg(op);//vy가 g에 의해 바뀜을 표현
}
void Drop::set_gravity(float k)
{
	gravity = k;
}
void Drop::set_vyg(Drop* op)
{
	op->set_vy(op->get_vy() + gravity);
}