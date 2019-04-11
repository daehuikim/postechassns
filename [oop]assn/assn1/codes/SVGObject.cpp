#include "SVGobject.h"//SVGObject class를 사용하기 위한 참조
#include "SVGAttribute.h"//SVGAttribute class를 사용하기 위한 참조
#include "SVGObjectList.h"
#include "SVGAttributeList.h"
#include <string>
#include <iostream>
using namespace std;

SVGObject::SVGObject()
{
	apParent = NULL;
	next = NULL;
	apChildList = NULL;
	apAttributeList = NULL;

}

void SVGObject::AppendChild(SVGObject* pChild)
{
	apChildList->AddSvgObject(pChild);//childlist에 child를 추가해준다.
}
void SVGObject::AddAttribute(SVGAttribute* pAttribute)
{
	apAttributeList->AddSvgAttribute(pAttribute);//attributelist에 attribute를 추가
}
void SVGObject::SetTagName(string tagName)
{
	aTagName = tagName;//이름을 설정해주는함수
}
string SVGObject::GetTagName()
{
	return aTagName;//GetTagName함수에서 priavate변수인 aTagName return
}
void SVGObject::SetNext(SVGObject* n)
{
	next = n;//다음노드를설정
}
SVGObject* SVGObject::GetNext()
{
	return next;//next포인터 생성을 위해private data를 get
}
void SVGObject::SetChildlist(SVGObjectList*list)
{
	apChildList = list;//childlist를 받아온다
}
SVGObjectList* SVGObject::Getchildlist()
{
	return apChildList;//childlist를 리턴해온다
}
void SVGObject::SetParent(SVGObject* parent)
{
	apParent = parent;//부모노드를 설정
}
SVGObject* SVGObject::GetParent()
{
	return apParent;//부모노드를 받아온다
}
SVGAttribute* SVGObject::GetHeadAttribute()//2차원인거->한번에 어트러뷰트리스트의 헤드노드까지불러옴
{
	return apAttributeList->GetHead();
}
void SVGObject::SetHeadAttribute(SVGAttribute* at)//2차원인거>한번에 리스트의 헤드노드까지설정
{
	at = apAttributeList->GetHead();
}
SVGAttributeList* SVGObject::GetAttributeList()//어트러뷰트리스트 리턴
{
	return apAttributeList;
}
SVGObject* SVGObject::GetFirstChild()//2차원인거->한번에 차일드리스트의 헤드노드까지불러옴
{
	return apChildList->GetHead();
}
void SVGObject::SetAttributeList(SVGAttributeList* al)//어트러뷰트리스트 설정
{
	apAttributeList = al;
}
