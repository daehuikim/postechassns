#include "Selection.h"
#include "SVGObject.h"
#include <string>
using namespace std;

Selection::Selection()//constructor�� �ʱ�ȭ
{
	next = NULL;
	apSVGobject = NULL;
}
void Selection::SetsvgObject(SVGObject* psvgObject)//selection�� object�� �־��ֱ� ���� �Լ�
{
	apSVGobject = psvgObject;
}
SVGObject* Selection :: GetsvgObject()//selection�ȿ� �ִ� object�� ���� ���� �Լ�
{
	return apSVGobject;
}
void Selection::SetNext(Selection* n)//nextnode�� �ޱ����� �Լ�
{
	next = n;
}
Selection* Selection::GetNext()//nextnode���� ��������Լ�
{
	return next;
}