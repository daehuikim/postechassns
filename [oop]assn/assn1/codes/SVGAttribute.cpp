#include "SVGAttribute.h"
#include <string>
using namespace std;
SVGAttribute::SVGAttribute()//constroctor
{
	next = NULL;
}
void SVGAttribute::SetName(string name)//�̸��� �޾��ִ� �Լ�
{
	aName = name;
}
string SVGAttribute::GetName()//�̸��� �������ִ� �Լ�
{
	return aName;
}
void SVGAttribute::SetValue(string a)//���� �޾��ִ� �Լ�
{
	aValue = a;
}
string SVGAttribute::GetValue()//���� �������ִ� �Լ�
{
	return aValue;
}
void SVGAttribute::SetNext(SVGAttribute* n)//������带 ����Ű�� ���ִ� �Լ�
{
	next = n;
}
SVGAttribute* SVGAttribute::GetNext()
{
	return next;//next������ ������ ����private data�� get
}