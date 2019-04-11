#include "SVGObjectList.h"
#include "SVGObject.h"
#include <string>
using namespace std;

SVGObjectList::SVGObjectList()//constroctor
{
	apHead = NULL;
	aTail = NULL;
	aSize = 0;
}
void SVGObjectList::AddSvgObject(SVGObject* pObject)
{
	if (apHead == NULL)//object들을 추가해줄때 아무것도 없으면헤드
	{
		apHead = pObject;
		aTail = pObject;
		aSize++;
	}
	else//있으면은 맨뒤에칸부터 넣어준다
	{
		aTail->SetNext(pObject);
		aTail = pObject;
		aSize++;
	}
	setSize(aSize);
}
void RemoveSvgObject(SVGObject* pObject)
{
	delete pObject;//delete로 동적할당한 메모리를 삭제
}
void SVGObjectList::SetHead(SVGObject* pHead)
{
	apHead = pHead;//list의 head를 parameter로 지정
}
SVGObject* SVGObjectList::GetHead()
{
	return apHead;//헤드값리턴하는함수
}
int SVGObjectList::GetSize()
{
	return aSize;  //사이즈리턴하는함수
}
void SVGObjectList::setSize(int a)
{
	aSize = a;//사이즈를 설정해주는함수
}
void SVGObjectList::Clear()
{
	while (apHead != NULL)
	{
		if (aSize == 1)//list를 비우기 위해 head를 없애준다.
		{
			aTail = NULL;
			apHead = NULL;
			aSize--;
		}
		else if (aSize > 1)//다없어질때까지 clear
		{
			SVGObject* temp = apHead;
			apHead = apHead->GetNext();
			delete temp;
			aSize--;
		}
	}
}