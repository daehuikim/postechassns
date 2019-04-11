#include "Selection.h"
#include "SVGObject.h"
#include <string>
using namespace std;

Selection::Selection()//constructor로 초기화
{
	next = NULL;
	apSVGobject = NULL;
}
void Selection::SetsvgObject(SVGObject* psvgObject)//selection에 object를 넣어주기 위한 함수
{
	apSVGobject = psvgObject;
}
SVGObject* Selection :: GetsvgObject()//selection안에 있는 object를 고르기 위한 함수
{
	return apSVGobject;
}
void Selection::SetNext(Selection* n)//nextnode를 받기위한 함수
{
	next = n;
}
Selection* Selection::GetNext()//nextnode값을 얻기위한함수
{
	return next;
}