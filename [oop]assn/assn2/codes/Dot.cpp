#include"Dot.h"
class Dot;//�ʱ�ȭ�� erase�κп� ���� get,set
Dot::Dot()
{
	erase = 0;
}
void Dot::set_erase(float k)
{
	erase = k;
}
bool Dot::get_erase()
{
	return erase;
}