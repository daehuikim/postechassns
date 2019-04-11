#include"Dot.h"
class Dot;//초기화와 erase부분에 대한 get,set
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