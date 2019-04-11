#include "SelectionList.h"
#include "Selection.h"
#include "SVGObject.h"
#include "SVGAttribute.h"
#include "SVGAttributeList.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

SelectionList::SelectionList()
{
	apHead=NULL;
	aTail=NULL;
	next=NULL;
	aSize = 0;
}//constroctor
void SelectionList::AddSelection(Selection* pSelection)//selectionlist에 selectionnode를 넣어주는 함수
{
	if (apHead == NULL)
	{
		apHead = pSelection;//하나도 없을 경우헤드테일지정
		aTail = pSelection;
		aSize++;
	}
	else
	{
		aTail->SetNext(pSelection);//테일뒤에 object를 하나씩달아준다.(이부분작동안함)
		aTail = pSelection;
		aSize++;
	}
}
void SelectionList::RemoveSelection(Selection* pSelection)//selection에 있는 노드자체를 없애는 함수
{
	apHead=pSelection->GetNext();//셀렉션리스트의 헤드를 옮겨준후 노드자체를 삭제한다
	delete pSelection->GetsvgObject();
	aSize--;
}
void SelectionList::Clear()
{
	while (apHead != NULL)
	{
		if (aSize == 1)//list를 비우기 위해 head를 없애준다.
		{

			aTail = NULL;
			apHead = NULL;
			aSize--;
		}
		else if (aSize > 1)//만약 헤드가 아니면 헤드가나올때까지delete
		{
			Selection* temp = apHead;
			apHead = apHead->GetNext();
			delete temp;
			aSize--;
		}
	}
}
void SelectionList::SetHead(Selection* pHead)
{
	apHead = pHead;//head를 phead에다 set
}//head설정함수
Selection* SelectionList::GetHead()
{
	return apHead;//selection의 head를 get
}//headnode를 받기 위한 함수
int SelectionList::GetSize()
{
	return aSize;
}//size값을 받아내는 함수
void SelectionList::PrintList(SVGObject* svg)//한줄씩만책임진다.
{
	Selection* node = new Selection;
	SVGObject* search = new SVGObject;
	SVGAttribute* att = new SVGAttribute;
	SVGAttributeList* li = new SVGAttributeList;
	search = svg;
	li = svg->GetAttributeList();
	svg->SetAttributeList(li);
	if (svg->GetAttributeList() != NULL)//attribute출력하는부분임
		att = li->GetHead();
	int a = 1,count(0);
	while (search->GetParent()!=NULL) 
	{
		cout << "\t";
		search = search->GetParent();//층만큼의 탭을 쳐준다.
	}search = svg;
	//selection감지함수
	Selected(svg);
	cout << "<" << svg->GetTagName();//svg를 출력하는부분
	if (svg->GetAttributeList() == NULL)
		cout << ">";
	else if (svg->GetAttributeList() != NULL)//attribute를 출력하는 부분임
	{
		while (att!= NULL)
		{
			cout << " " << att->GetName() << "=" << "\"" << att->GetValue() << "\"";
			att = att->GetNext();
		}cout << ">";
	}
	if (svg->Getchildlist() != NULL)
		cout << "\n";
	if (svg->Getchildlist() != NULL)
	{
		if(svg->GetFirstChild()!=NULL)
		PrintList(svg->GetFirstChild());
	}
	if (svg->GetNext() != NULL)//형제가있는지 조사
	{
		cout << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
		PrintList(svg->GetNext());
	}
	if (svg->Getchildlist() == NULL && svg->GetNext() == NULL)
	{
		cout << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
	}

	
	if (a == 1)//태그네임을 달아준다. 앞서 출력을 다했으면 태그네임을 달아줌
	{
		while (search->GetParent() != NULL)
		{
			cout << "\t";
			search = search->GetParent();//층만큼의 탭을 쳐준다.
		}
		cout << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
	}
}
void SelectionList::Selected(SVGObject* svg)
{
	Selection* sear = new Selection;
	SVGObject* psel = new SVGObject;
	sear = apHead;
	for (int i=0;i<aSize;i++)
	{
		if (sear == NULL)
			break;
		psel = sear->GetsvgObject();
		if (psel==svg)
		{
			cout << "*";
			break;
		}
		if (sear->GetNext() == NULL)
			break;
		sear = sear->GetNext();
	}//selection list와 비교해서 같은 노드이면 select표시를 해준다.
}
void SelectionList::PrintListw(SVGObject* svg)//한줄씩만책임진다.
{
	Selection* node = new Selection;
	SVGObject* search = new SVGObject;
	SVGAttribute* att = new SVGAttribute;
	SVGAttributeList* li = new SVGAttributeList;
	search = svg;
	li = svg->GetAttributeList();
	svg->SetAttributeList(li);
	if (svg->GetAttributeList() != NULL)//attribute출력하는부분임
		att = li->GetHead();
	int a = 1, count(0);
	while (search->GetParent() != NULL)
	{
		cout << "\t";
		search = search->GetParent();//층만큼의 탭을 쳐준다.
	}search = svg;
	cout << "<" << svg->GetTagName();//svg를 출력하는부분
	if (svg->GetAttributeList() == NULL)
		cout << ">";
	else if (svg->GetAttributeList() != NULL)//attribute를 출력하는 부분임
	{
		while (att != NULL)
		{
			cout << " " << att->GetName() << "=" << "\"" << att->GetValue() << "\"";
			att = att->GetNext();
		}cout << ">";
	}
	if (svg->Getchildlist() != NULL)
		cout << "\n";
	if (svg->Getchildlist() != NULL)//자식이 있는지 여부 조사-list들이 널포인터
	{
		if (svg->GetFirstChild() != NULL)
		PrintListw(svg->GetFirstChild());
	}
	if (svg->GetNext() != NULL)//형제가있는지 조사
	{
		cout << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
		PrintListw(svg->GetNext());
	}
	if (svg->Getchildlist() == NULL && svg->GetNext() == NULL)
	{
		cout << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
	}


	if (a == 1)//태그네임을 달아준다. 앞서 출력을 다했으면 태그네임을 달아줌
	{
		while (search->GetParent() != NULL)
		{
			cout << "\t";
			search = search->GetParent();//층만큼의 탭을 쳐준다.
		}
		cout << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
	}
}//별을 빼주고 출력하는 함수로 PrintList와 같지만 Selected함수를 거치지 않는다.
void SelectionList::PrintListf(SVGObject* svg, ofstream &outfile)
{
	Selection* node = new Selection;
	SVGObject* search = new SVGObject;
	SVGAttribute* att = new SVGAttribute;
	SVGAttributeList* li = new SVGAttributeList;
	search = svg;
	li = svg->GetAttributeList();
	svg->SetAttributeList(li);
	if (svg->GetAttributeList() != NULL)//attribute출력하는부분임
		att = li->GetHead();
	int a = 1, count(0);
	while (search->GetParent() != NULL)
	{
		outfile << "\t";
		search = search->GetParent();//층만큼의 탭을 쳐준다.
	}search = svg;
	outfile << "<" << svg->GetTagName();//svg를 출력하는부분
	if (svg->GetAttributeList() == NULL)
		outfile << ">";
	else if (svg->GetAttributeList() != NULL)//attribute를 출력하는 부분임
	{
		while (att != NULL)
		{
			outfile << " " << att->GetName() << "=" << "\"" << att->GetValue() << "\"";
			att = att->GetNext();
		}outfile << ">";
	}
	if (svg->Getchildlist() != NULL)
		outfile << "\n";
	if (svg->Getchildlist() != NULL)//자식이 있는지 여부 조사-list들이 널포인터
	{
		if (svg->GetFirstChild() != NULL)
		PrintListf(svg->GetFirstChild(),outfile);
	}
	if (svg->GetNext() != NULL)//형제가있는지 조사
	{
		outfile << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
		PrintListf(svg->GetNext(), outfile);
	}
	if (svg->Getchildlist() == NULL && svg->GetNext() == NULL)
	{
		outfile << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
	}


	if (a == 1)//태그네임을 달아준다. 앞서 출력을 다했으면 태그네임을 달아줌
	{
		while (search->GetParent() != NULL)
		{
			outfile << "\t";
			search = search->GetParent();//층만큼의 탭을 쳐준다.
		}
		outfile << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
	}
}//위 print함수들과 내용은 같고 파일로 출력하기 때문에 cout부분이 outfile로 바뀌어있다.
