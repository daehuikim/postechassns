#include "SVGAttribute.h"
#include <string>
using namespace std;
SVGAttribute::SVGAttribute()//constroctor
{
	next = NULL;
}
void SVGAttribute::SetName(string name)//이름을 받아주는 함수
{
	aName = name;
}
string SVGAttribute::GetName()//이름을 리턴해주는 함수
{
	return aName;
}
void SVGAttribute::SetValue(string a)//값을 받아주는 함수
{
	aValue = a;
}
string SVGAttribute::GetValue()//값을 리턴해주는 함수
{
	return aValue;
}
void SVGAttribute::SetNext(SVGAttribute* n)//다음노드를 가르키게 해주는 함수
{
	next = n;
}
SVGAttribute* SVGAttribute::GetNext()
{
	return next;//next포인터 생성을 위해private data를 get
}