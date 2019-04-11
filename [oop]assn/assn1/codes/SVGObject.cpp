#include "SVGobject.h"//SVGObject class�� ����ϱ� ���� ����
#include "SVGAttribute.h"//SVGAttribute class�� ����ϱ� ���� ����
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
	apChildList->AddSvgObject(pChild);//childlist�� child�� �߰����ش�.
}
void SVGObject::AddAttribute(SVGAttribute* pAttribute)
{
	apAttributeList->AddSvgAttribute(pAttribute);//attributelist�� attribute�� �߰�
}
void SVGObject::SetTagName(string tagName)
{
	aTagName = tagName;//�̸��� �������ִ��Լ�
}
string SVGObject::GetTagName()
{
	return aTagName;//GetTagName�Լ����� priavate������ aTagName return
}
void SVGObject::SetNext(SVGObject* n)
{
	next = n;//������带����
}
SVGObject* SVGObject::GetNext()
{
	return next;//next������ ������ ����private data�� get
}
void SVGObject::SetChildlist(SVGObjectList*list)
{
	apChildList = list;//childlist�� �޾ƿ´�
}
SVGObjectList* SVGObject::Getchildlist()
{
	return apChildList;//childlist�� �����ؿ´�
}
void SVGObject::SetParent(SVGObject* parent)
{
	apParent = parent;//�θ��带 ����
}
SVGObject* SVGObject::GetParent()
{
	return apParent;//�θ��带 �޾ƿ´�
}
SVGAttribute* SVGObject::GetHeadAttribute()//2�����ΰ�->�ѹ��� ��Ʈ����Ʈ����Ʈ�� ���������ҷ���
{
	return apAttributeList->GetHead();
}
void SVGObject::SetHeadAttribute(SVGAttribute* at)//2�����ΰ�>�ѹ��� ����Ʈ�� ������������
{
	at = apAttributeList->GetHead();
}
SVGAttributeList* SVGObject::GetAttributeList()//��Ʈ����Ʈ����Ʈ ����
{
	return apAttributeList;
}
SVGObject* SVGObject::GetFirstChild()//2�����ΰ�->�ѹ��� ���ϵ帮��Ʈ�� ���������ҷ���
{
	return apChildList->GetHead();
}
void SVGObject::SetAttributeList(SVGAttributeList* al)//��Ʈ����Ʈ����Ʈ ����
{
	apAttributeList = al;
}
