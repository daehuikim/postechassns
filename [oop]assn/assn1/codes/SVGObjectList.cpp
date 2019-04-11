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
	if (apHead == NULL)//object���� �߰����ٶ� �ƹ��͵� ���������
	{
		apHead = pObject;
		aTail = pObject;
		aSize++;
	}
	else//�������� �ǵڿ�ĭ���� �־��ش�
	{
		aTail->SetNext(pObject);
		aTail = pObject;
		aSize++;
	}
	setSize(aSize);
}
void RemoveSvgObject(SVGObject* pObject)
{
	delete pObject;//delete�� �����Ҵ��� �޸𸮸� ����
}
void SVGObjectList::SetHead(SVGObject* pHead)
{
	apHead = pHead;//list�� head�� parameter�� ����
}
SVGObject* SVGObjectList::GetHead()
{
	return apHead;//��尪�����ϴ��Լ�
}
int SVGObjectList::GetSize()
{
	return aSize;  //��������ϴ��Լ�
}
void SVGObjectList::setSize(int a)
{
	aSize = a;//����� �������ִ��Լ�
}
void SVGObjectList::Clear()
{
	while (apHead != NULL)
	{
		if (aSize == 1)//list�� ���� ���� head�� �����ش�.
		{
			aTail = NULL;
			apHead = NULL;
			aSize--;
		}
		else if (aSize > 1)//�پ����������� clear
		{
			SVGObject* temp = apHead;
			apHead = apHead->GetNext();
			delete temp;
			aSize--;
		}
	}
}