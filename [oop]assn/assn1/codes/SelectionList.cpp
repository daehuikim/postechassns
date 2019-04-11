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
void SelectionList::AddSelection(Selection* pSelection)//selectionlist�� selectionnode�� �־��ִ� �Լ�
{
	if (apHead == NULL)
	{
		apHead = pSelection;//�ϳ��� ���� ��������������
		aTail = pSelection;
		aSize++;
	}
	else
	{
		aTail->SetNext(pSelection);//���ϵڿ� object�� �ϳ����޾��ش�.(�̺κ��۵�����)
		aTail = pSelection;
		aSize++;
	}
}
void SelectionList::RemoveSelection(Selection* pSelection)//selection�� �ִ� �����ü�� ���ִ� �Լ�
{
	apHead=pSelection->GetNext();//�����Ǹ���Ʈ�� ��带 �Ű����� �����ü�� �����Ѵ�
	delete pSelection->GetsvgObject();
	aSize--;
}
void SelectionList::Clear()
{
	while (apHead != NULL)
	{
		if (aSize == 1)//list�� ���� ���� head�� �����ش�.
		{

			aTail = NULL;
			apHead = NULL;
			aSize--;
		}
		else if (aSize > 1)//���� ��尡 �ƴϸ� ��尡���ö�����delete
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
	apHead = pHead;//head�� phead���� set
}//head�����Լ�
Selection* SelectionList::GetHead()
{
	return apHead;//selection�� head�� get
}//headnode�� �ޱ� ���� �Լ�
int SelectionList::GetSize()
{
	return aSize;
}//size���� �޾Ƴ��� �Լ�
void SelectionList::PrintList(SVGObject* svg)//���پ���å������.
{
	Selection* node = new Selection;
	SVGObject* search = new SVGObject;
	SVGAttribute* att = new SVGAttribute;
	SVGAttributeList* li = new SVGAttributeList;
	search = svg;
	li = svg->GetAttributeList();
	svg->SetAttributeList(li);
	if (svg->GetAttributeList() != NULL)//attribute����ϴºκ���
		att = li->GetHead();
	int a = 1,count(0);
	while (search->GetParent()!=NULL) 
	{
		cout << "\t";
		search = search->GetParent();//����ŭ�� ���� ���ش�.
	}search = svg;
	//selection�����Լ�
	Selected(svg);
	cout << "<" << svg->GetTagName();//svg�� ����ϴºκ�
	if (svg->GetAttributeList() == NULL)
		cout << ">";
	else if (svg->GetAttributeList() != NULL)//attribute�� ����ϴ� �κ���
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
	if (svg->GetNext() != NULL)//�������ִ��� ����
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

	
	if (a == 1)//�±׳����� �޾��ش�. �ռ� ����� �������� �±׳����� �޾���
	{
		while (search->GetParent() != NULL)
		{
			cout << "\t";
			search = search->GetParent();//����ŭ�� ���� ���ش�.
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
	}//selection list�� ���ؼ� ���� ����̸� selectǥ�ø� ���ش�.
}
void SelectionList::PrintListw(SVGObject* svg)//���پ���å������.
{
	Selection* node = new Selection;
	SVGObject* search = new SVGObject;
	SVGAttribute* att = new SVGAttribute;
	SVGAttributeList* li = new SVGAttributeList;
	search = svg;
	li = svg->GetAttributeList();
	svg->SetAttributeList(li);
	if (svg->GetAttributeList() != NULL)//attribute����ϴºκ���
		att = li->GetHead();
	int a = 1, count(0);
	while (search->GetParent() != NULL)
	{
		cout << "\t";
		search = search->GetParent();//����ŭ�� ���� ���ش�.
	}search = svg;
	cout << "<" << svg->GetTagName();//svg�� ����ϴºκ�
	if (svg->GetAttributeList() == NULL)
		cout << ">";
	else if (svg->GetAttributeList() != NULL)//attribute�� ����ϴ� �κ���
	{
		while (att != NULL)
		{
			cout << " " << att->GetName() << "=" << "\"" << att->GetValue() << "\"";
			att = att->GetNext();
		}cout << ">";
	}
	if (svg->Getchildlist() != NULL)
		cout << "\n";
	if (svg->Getchildlist() != NULL)//�ڽ��� �ִ��� ���� ����-list���� ��������
	{
		if (svg->GetFirstChild() != NULL)
		PrintListw(svg->GetFirstChild());
	}
	if (svg->GetNext() != NULL)//�������ִ��� ����
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


	if (a == 1)//�±׳����� �޾��ش�. �ռ� ����� �������� �±׳����� �޾���
	{
		while (search->GetParent() != NULL)
		{
			cout << "\t";
			search = search->GetParent();//����ŭ�� ���� ���ش�.
		}
		cout << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
	}
}//���� ���ְ� ����ϴ� �Լ��� PrintList�� ������ Selected�Լ��� ��ġ�� �ʴ´�.
void SelectionList::PrintListf(SVGObject* svg, ofstream &outfile)
{
	Selection* node = new Selection;
	SVGObject* search = new SVGObject;
	SVGAttribute* att = new SVGAttribute;
	SVGAttributeList* li = new SVGAttributeList;
	search = svg;
	li = svg->GetAttributeList();
	svg->SetAttributeList(li);
	if (svg->GetAttributeList() != NULL)//attribute����ϴºκ���
		att = li->GetHead();
	int a = 1, count(0);
	while (search->GetParent() != NULL)
	{
		outfile << "\t";
		search = search->GetParent();//����ŭ�� ���� ���ش�.
	}search = svg;
	outfile << "<" << svg->GetTagName();//svg�� ����ϴºκ�
	if (svg->GetAttributeList() == NULL)
		outfile << ">";
	else if (svg->GetAttributeList() != NULL)//attribute�� ����ϴ� �κ���
	{
		while (att != NULL)
		{
			outfile << " " << att->GetName() << "=" << "\"" << att->GetValue() << "\"";
			att = att->GetNext();
		}outfile << ">";
	}
	if (svg->Getchildlist() != NULL)
		outfile << "\n";
	if (svg->Getchildlist() != NULL)//�ڽ��� �ִ��� ���� ����-list���� ��������
	{
		if (svg->GetFirstChild() != NULL)
		PrintListf(svg->GetFirstChild(),outfile);
	}
	if (svg->GetNext() != NULL)//�������ִ��� ����
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


	if (a == 1)//�±׳����� �޾��ش�. �ռ� ����� �������� �±׳����� �޾���
	{
		while (search->GetParent() != NULL)
		{
			outfile << "\t";
			search = search->GetParent();//����ŭ�� ���� ���ش�.
		}
		outfile << "</" << svg->GetTagName() << ">" << endl;
		a = 0;
	}
}//�� print�Լ���� ������ ���� ���Ϸ� ����ϱ� ������ cout�κ��� outfile�� �ٲ���ִ�.
