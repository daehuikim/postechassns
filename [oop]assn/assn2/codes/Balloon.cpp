#include "Balloon.h"
//balloon member에 대한 멤버 초기화와 get,set부분이 담겨 있다.
Balloon::Balloon ()
{
	popping=0;
}
void Balloon::update(Balloon* op)
{
	op->set_ra(op->get_rad() + op->get_vr());//vr에 대하여 r이 늘어나는 부분을 나타냈다.
}
void Balloon::pop(Balloon* op)
{
	op->set_ra(0);//만약 pop하게 된다면 vr과 radius를 각각 0으로 만들어서 풍선이 터지게 한다.
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