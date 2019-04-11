#include "SVGAttributeList.h"
#include "SVGAttribute.h"
using namespace std;
SVGAttributeList::SVGAttributeList()//constroctor로 초기화
{
	apHead = NULL;
	aTail = NULL;
	aSize = 0;
}
void SVGAttributeList::AddSvgAttribute(SVGAttribute* pAttribute)
{
	if (apHead == NULL)//리스트에 하나도 없을 경우는 헤드로 지정해준다.
	{
		apHead = pAttribute;
		aTail = pAttribute;
		aSize++;
	}
	else//리스트에 미리 노드가 존재하면 꼬리부터 순서대로 달아준다.
	{
		aTail->SetNext(pAttribute);
		aTail = pAttribute;
		aSize++;
	}
}
void SVGAttributeList::SetHead(SVGAttribute*pHead)//head를설정해준다
{
	apHead = pHead;
}
SVGAttribute* SVGAttributeList::GetHead()//headnode를 받아준다
{
	return apHead;
}
int  SVGAttributeList::GetSize()//size값을 리턴한다
{
	return aSize;
}