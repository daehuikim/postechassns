#include "SVGAttributeList.h"
#include "SVGAttribute.h"
using namespace std;
SVGAttributeList::SVGAttributeList()//constroctor�� �ʱ�ȭ
{
	apHead = NULL;
	aTail = NULL;
	aSize = 0;
}
void SVGAttributeList::AddSvgAttribute(SVGAttribute* pAttribute)
{
	if (apHead == NULL)//����Ʈ�� �ϳ��� ���� ���� ���� �������ش�.
	{
		apHead = pAttribute;
		aTail = pAttribute;
		aSize++;
	}
	else//����Ʈ�� �̸� ��尡 �����ϸ� �������� ������� �޾��ش�.
	{
		aTail->SetNext(pAttribute);
		aTail = pAttribute;
		aSize++;
	}
}
void SVGAttributeList::SetHead(SVGAttribute*pHead)//head���������ش�
{
	apHead = pHead;
}
SVGAttribute* SVGAttributeList::GetHead()//headnode�� �޾��ش�
{
	return apHead;
}
int  SVGAttributeList::GetSize()//size���� �����Ѵ�
{
	return aSize;
}