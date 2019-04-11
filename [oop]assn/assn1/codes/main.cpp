#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include "SVGObject.h"
#include "SVGObjectList.h"
#include "SVGAttribute.h"
#include "SVGAttributeList.h"
#include "Selection.h"
#include "SelectionList.h"
using namespace std;

int main()
{
	string m, command[4] = { " " };
	int  num = 0;

	SVGObject* root = new SVGObject;//ó�� root�� ������� �����Ҵ�
	Selection* selecti = new Selection;//selectionlist�� �־��� selection�� �Ҵ�
	SelectionList* sl = new SelectionList;//selection��ɾ��� ������� ���� selectionlist
	SVGObject* pselect = new SVGObject;//���� �������� ���� pselect��� svgobject����
	SVGObjectList* pList = new SVGObjectList;
	root->SetTagName("HTML");//���α׷������ root selection�� �����Ѵ�.
	pselect = root;
	selecti->SetsvgObject(pselect);
	sl->AddSelection(selecti);//�� �� root�� ����Ʈ�Ѵ�.

	while (1)
	{
		cout << "<SVGmaker>";//��ɾ �Է¹޴� �κ��̴�.
		getline(cin, m);
		stringstream ss(m);
		string temp, numstring;
		int i = 0,check=0;//check���� ������ �־� ��ɾ� ���࿩�θ� �����Ѵ�.
		command[0] = " ", command[1] = " ", command[2] = " ",command[3]=" ", num = 0;//��� ��ɾ ���� ����ó���� ���ؼ� �׻� �ʱ�ȭ�� ��.
		while (ss >> temp)//string stream�� �̿��ؼ� space�� �������� parsing
		{
			if (i < 2)//�� ó�� �ΰ��� ��ɾ command�� �޴´�.
				command[i] = temp;
			if (i == 2)
			{
				command[2] = temp;
				numstring = command[2];//string���� �ϳ��޴´�.
			}
			if (i == 3)
				command[3] = temp;
			i++;
		}

		if (command[0] == "append")
		{
			check = 1;//append�� ����Ǿ����� Ȯ���ϴ°�
			if (numstring.size() != 0)//������ ���� string���� ����ϱ� ���� int�� �ٲ��ش�.
				num = stoi(numstring);
			Selection* one = new Selection;
			one = sl->GetHead();
			if (num == 0)
				num = 1;
			sl->Clear();//�׻� ������ϱ������� ���� ������ ����Ʈ�� ����ְ� ���� ����� �� ��ü�� ����Ʈ�ϵ��� selection�̵��� �����Ѵ�.
			for (i = 0; i < num; i++)
			{
				if (command[3] != " ")
				{
					sl->AddSelection(one);
					break;
				}
				if (one->GetsvgObject()->Getchildlist() == NULL)//���� childlist�� ���� ���, �� ������ ������ ���� ���� list�� �����ϰ� �ִ� ��쿡�� ���������ʰ� �� �ڿ� �̾�ܴ�.
				{
					SVGObjectList* cl = new SVGObjectList;
					one->GetsvgObject()->SetChildlist(cl);
				}
				SVGObject* SVG = new SVGObject;//append�ϱ� ���� ���ο� ��ü�� �������ְ� selection�� �Ҵ��Ѵ�.
				Selection* SEL = new Selection;
				SVG->SetTagName(command[1]);
				SVG->SetParent(one->GetsvgObject());
				one->GetsvgObject()->Getchildlist()->AddSvgObject(SVG);//����� ������ ���� childlist�� selectionlist�� �ִ� ������ ���ش�.
				SEL->SetsvgObject(SVG);
				sl->AddSelection(SEL);
				check = 0;
			}
		}
		if (command[0] == "select")
		{
			check = 2;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			int m(0);
			string tgnm;
			SVGObject* dam = new SVGObject;//ó���� ���� �����ǿ� ���� ������ dam��(����) dam�� ����
			SVGObject* par = new SVGObject;//���� �������� �θ� �ǹǷ� par(�з����ǹ�) �����ؼ� dam�� �켱 �����صд�.

			dam = sl->GetHead()->GetsvgObject();
			par = dam;
			if (numstring.size() != 0)//append���� ���������μ��ڸ� int�� �޾Ƽ� ����صд�.
				num = stoi(numstring);
			if (sl->GetSize() > 1 && command[1] != " ")//multiple-selection�϶��� select�� �ȵǵ��� �Ѵ�.
			{
				cout << "Wrong Command!" << endl;
				m = 1;//m���� ��ȭ�����־� �߸� �Է½� �� ������ ���ϵ��� �Ѵ�.
			}
			if (command[1] == " "&&m == 0)//�׳� select�� �Է����� ��� ������ Ʈ���� �����ֵ��� ����
			{
				sl->PrintList(root);
				continue;
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			}

			sl->Clear();//����Ʈ�� �ϱ� ���� �Ʊ� dam�� ���� ����Ʈ ������ ������ �������� ����ش�.
			if (command[1] != " "&&num == 0)//Ư���̸��� ��ü�� ��� ����Ʈ�� ����� �ݺ���
			{
				int a = 0;//a�� ��ȭ�� �������� select�� ���θ� �˷���. ��,�ڽ��� ���� ����� ����ó��
				for (SVGObject* temp = par->GetFirstChild(); temp != NULL; temp = temp->GetNext())//temp��� �˻��� ��ü�ּҸ� �̿��Ѵ�.
				{
					if (temp->GetTagName() == command[1])//��ɹ��� �ܾ�� �̸��� ���� ��� �����ǿ� �߰����ش�.
					{
						Selection* tong = new Selection;
						tong->SetsvgObject(temp);
						sl->AddSelection(tong);
						a = 1;
					}
				}if (a == 0)//���� �����ǿ� �ƹ��͵� �߰����� �ʾ����� ���� �������� ����Ų��.
				{
					cout << "Wrong Command! �ڽ��� �����ϴ�." << endl;
					Selection* tong = new Selection;
					tong->SetsvgObject(par);//������������ ���� par���
					sl->AddSelection(tong);
					cout << "selection is not changed." << endl;
				}
				cout << sl->GetSize() << "item(s) is selected!" << endl;//selection�� ���� �� ��� ����Ʈ �Ǿ����� ���
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			}
			else if (command[1] != " "&&num != 0)//Ư�� index�� �ϳ��� select�ϴ� ����� �ݺ����̴�. ������ ���� �Ȱ���.
			{
				int a = 0, b = 0;//a�� ���� childlist���� ������ check���ְ� b�δ� ����Ʈ ���θ� üũ�Ѵ�.
				for (SVGObject* temp = par->GetFirstChild(); temp != NULL; temp = temp->GetNext())
				{
					if (temp->GetTagName() == command[1])
					{
						a++;
					}
					if (a == num)
					{
						Selection* tong = new Selection;
						tong->SetsvgObject(temp);
						sl->AddSelection(tong);
						b = 1;
					}
				}if (b == 0)//�Ʊ�� ���������� ����Ʈ �� ��ü�� ���� ��� ���� �������� ����Ų��.
				{
					Selection* tong = new Selection;
					tong->SetsvgObject(par);
					sl->AddSelection(tong);
					cout << "selection is not changed." << endl;
				}
				cout << sl->GetSize() << "item(s) is selected!" << endl;//�ϳ��� ���õ� ���� �˷��ش�.
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			}
		}
		if (command[0] == "remove")
		{
			check = 3;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			SVGObject* ro = new SVGObject;//remove�ϱ� ���� �޾Ƴ��� ��ü�� �θ�ü�� �����Ѵ�.
			SVGObject* p = new SVGObject;
			Selection* ra = new Selection;//remove�� �� ���ο� selectionlist�� �־��� selection����
			ro = sl->GetHead()->GetsvgObject();
			p = ro->GetParent();
			if (ro->GetParent() == NULL)//parent�� remove���� ���ϰ� �Ѵ�.
			{
				cout << "Error! Wrong Command" << endl;
			}

			else
			{
				ro = p->GetFirstChild();//����ο��� p�� ���� ������ �� ��ü�� �θ��带 �޾Ƴ��� ro�� �� �ڽ��� �־� ó������ ������.
				for (Selection* temp = sl->GetHead(); temp != NULL;)
				{
					if (ro->GetNext() == temp->GetsvgObject())//���� �����ǵ� ��ü�� ã������ ro�� select�� ��ü�� ���Ͽ� ������ remove�Ѵ�.
					{
						ro->SetNext(ro->GetNext()->GetNext());//�����ϱ��� next��带 �������ش�.
						sl->RemoveSelection(temp);//selection list������ �������ϸ鼭 ���ÿ� ��ü�� �����Ѵ�.
						temp = temp->GetNext();
					}
					ro = ro->GetNext();//���� ������ ���ϸ� ���� ���� �˻��� �����Ѵ�.
				}
				sl->Clear();//������ �� ������ ����Ʈ�� ���� ��ó�� �޾Ƴ��� �θ�ü�� ����Ʈ�Ͽ� �������̵���������
				ra->SetsvgObject(p);
				sl->AddSelection(ra);
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			}
		}
		if (command[0] == "end")
		{
			check = 4;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			SVGObject *pa = new SVGObject;
			Selection* se = new Selection;

			pa = sl->GetHead()->GetsvgObject();//pa�� ���� �����Ǹ���Ʈ�� ��带 �־��ش�.

			if (command[1] == " ")
			{
				if (pa == root)
					cout << "Error! Wrong Command" << endl;//���� root��带 ������ ���� ��� �������� ���
				else
				{
					sl->Clear();//���� ������ ����Ʈ�� ���� ó�� �޾Ƴ��� �θ��带 �����ǿ� ä������ ������ �̵� �Ϸ�
					pa = pa->GetParent();//selection�� �θ���̵������ش�.
					se->SetsvgObject(pa);
					sl->AddSelection(se);
				}
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			}
			//�߰����� ��� ****************root end****************************
			else if (command[1] == "root")
			{
				if (pa == root)
					cout << "It's already root!" << endl;//root�ϰ�쿡�� error���
				else
				{
					while (pa != root)//�ݺ������� root�� ���ö����� ��� �����Ѵ�.
					{
						sl->Clear();//���� ������ ����Ʈ�� ���� ó�� �޾Ƴ��� �θ��带 �����ǿ� ä������ ������ �̵� �Ϸ�
						pa = pa->GetParent();//selection�� �θ���̵������ش�.
						se->SetsvgObject(pa);
						sl->AddSelection(se);
					}cout << "Now root is selected!" << endl;//root node�� ���õ��� �˷���
					check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
				}
			}
			else if (command[1] != "root"&&command[1] != " ")//�̹� ��Ʈ ��� �� ��� �ش� ��������� �������� �ʰ� ������ ���
			{
				cout << "You should enter 'root' or nothing." << endl;
			}
		}
		if (command[0] == "exit")
		{
			break;//exit�� �Է� �� while���� ���������鼭 ���α׷� ����
		}
		if (command[0] == "cattr")
		{
			check = 6;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			Selection* bs; //�޴� ������ Bat neon Selection�� �ձ���(�˼��մϴ� �����̸��� ���̻� �����ȳ�����..)
			SVGObject* sb;//�����Ǻ����̸��� �ݴ�� �� ������Ʈ���� ����
			int attSize(1), i, slSize;
			bs = sl->GetHead();//����selection�� head�� �ش�.
			slSize = sl->GetSize();//���� �����Ǹ���Ʈ�� ��
			for (i = 0; i < slSize; i++)//�����Ǹ���Ʈ�� ���ڸ�ŭ �ݺ����� ����.
			{
				sb = bs->GetsvgObject();
				if (sb->GetAttributeList() == NULL) {//���� attribute�� �ϳ��� ���� �����̸� list�� �����ؼ� �߰����ش�.
					SVGAttributeList* al = new SVGAttributeList;
					sb->SetAttributeList(al);
				}
				attSize = sb->GetAttributeList()->GetSize();
				SVGAttribute* pSelectAtt = new SVGAttribute;//�߰��� attribute����
				pSelectAtt->SetName(command[1]);
				pSelectAtt->SetValue(numstring);
				int y = 0;
				for (SVGAttribute* temp = sb->GetAttributeList()->GetHead(); temp != NULL; temp = temp->GetNext())//���� �̹� attribute�� ���� ��� �̸��� �ٲٰų� �߰����ֱ� ���� ��ü attributelist�� �˻��Ѵ�.
				{
					if (temp->GetName() == command[1])//�����̸��� attribute�� �����ٲ�
					{
						temp->SetValue(numstring);//�����ٲپ��ش�.
						y = 1;//���� �ٲ� �� ���� �ٸ� attribute�� �̸� �� �� �̸��� �޶� �� �߰��ұ�� y���� �����Ŵ���� ���ο� ��带 �߰����� �ʾƵ� �Ǵ� ���� �˷���
					}
				}
				if (y == 0)
				{
					sb->GetAttributeList()->AddSvgAttribute(pSelectAtt);//���ο� Attribute�߰�
				}
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
				if (bs->GetNext() == NULL)
					break;//��������������
				bs = bs->GetNext();//�������������ΰ˻�
			}
		}
		if (command[0] == "tattr")
		{
			check = 7;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			if (numstring.size() != 0)//numstring�� int�κ�ȯ�����ش�.
				num = stoi(numstring);
			float n1(0), n2(0);
			string f1, f2;
			f1 = to_string(n1), f2 = to_string(n2);//float���� string���� ����ؾ� �ϱ� ������ string���� �����Ѵ�.
			Selection* bs;//���� ��� ���� ������ cattr�� �����ϰ� �Ǿ��ִ�.
			SVGObject* sb;
			int attSize(1), i, slSize;

			bs = sl->GetHead();//����selection�� hea
			slSize = sl->GetSize();//���� �����Ǹ���Ʈ�� ��
			for (i = 0; i < slSize; i++)
			{
				sb = bs->GetsvgObject();
				if (sb->GetAttributeList() == NULL) {//���� attribute�� �ϳ��� ���� �����̸� list�� �����ؼ� �߰����ش�.
					SVGAttributeList* al = new SVGAttributeList;
					sb->SetAttributeList(al);
				}
				attSize = sb->GetAttributeList()->GetSize();
				SVGAttribute* pSelectAtt = new SVGAttribute;//�߰��� attribute����
				pSelectAtt->SetName("transform");//tattr�� ��� Ư���� �̸��� ���� ���� �����Ƿ� �������ش�.
				pSelectAtt->SetValue("translate(" + f1 + "," + f2 + ")");//�̷� �������� string�� �ٿ��� ������ش�. ó������f1,f2���� 0���� ����ο��� �ʱ�ȭ�ߴ�.
				int y = 0;
				for (SVGAttribute* temp = sb->GetAttributeList()->GetHead(); temp != NULL; temp = temp->GetNext())//���� �̹� attribute�� ���� ��� �̸��� �ٲٰų� �߰����ֱ� ���� ��ü attributelist�� �˻��Ѵ�.
				{

					if (temp->GetName() == command[1])//�����̸��� attribute�� �����ٲ�
					{
						temp->SetValue(numstring);//�����ٲپ��ش�.
						y = 1;//���� �ٲ� �� ���� �ٸ� attribute�� �̸� �� �� �̸��� �޶� �� �߰��ұ�� y���� �����Ŵ���� ���ο� ��带 �߰����� �ʾƵ� �Ǵ� ���� �˷���
					}
				}
				if (y == 0)
				{
					sb->GetAttributeList()->AddSvgAttribute(pSelectAtt);//���ο� Attribute�߰�
				}
				n1 = n1 + stoi(command[1]), n2 = n2 + num;//�Է��� ���� ���� ��ŭ ���������ִ� �����̴�.
				f1 = to_string(n1), f2 = to_string(n2);
				if (bs->GetNext() == NULL)
					break;//��������������
				bs = bs->GetNext();//�������������ΰ˻�
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			}
		}
		if (command[0] == "print")
		{
			check = 8;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			if (command[1] == " ")
			{
				sl->PrintListw(root);//���� �׳� print�� ����ϸ� *�� �����Ͽ� ����Ʈ�� ��½����ֵ��� �ϴ� �Լ��� ȣ���Ѵ�.
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			}
			else//���� �̸��� �Է��ϸ� �ش����ϸ��� ���� ���Ϸ� ����ϰ� ���ش�.
			{
				string filename;
				filename = command[1];
				ofstream File;
				File.open(filename);
				sl->PrintListf(root, File);
				File.close();
				cout << "\"" << filename << "\"" << "file is created" << endl;
				check = 0;//check���� ��ȭ�� �־� �߸��Էµ� ��츦 ��Ƴ�
			}
		}
		if (command[0] == "help"||check!=0)//�߸��� ��ɾ �־� ����ȵ� ��쵵 ����Ǿ�� �ϹǷ�check���ǵ� ����
		{
			check = 9;
			ifstream help;
			string com, use, condition, des, tem, nm;//��ɾ���� �޾� ���� string�� ����
			char total[300];//strtok�Լ��� ����ϱ� ���� char�� char�����͸� �����Ѵ�.
			char* ptr, *context = NULL;
			int p(0);
			help.open("help.csv");
			if (command[1] == " ") {//�׳� help�� �Է��� ��� getline���� �� ���� ä�� ���� �� ,�� �������� �ڸ���.
				for (int i = 0; i < 10; i++)
				{
					help.getline(total, 300);
					if (i == 0)
						continue;
					ptr = strtok(total, ",");//ù��°�� name�κ��̴� �ڸ� �� �ƹ� ó���� ���� �ʴ´�.
					ptr = strtok(NULL, ",");//�ι�°�� usage�� ��������Ƿ� �̸� �ݺ������� ����Ʈ���ش�.
					cout << ptr << endl;
					check = 0;
				}
			}
			if (command[1] != " "&&check != 0&&command[0]=="help")//���� Ư�� ��ɾ �ִ� ����� ���� ���� �Ѱ����� ��� ������ ������ش�.
			{
				for (int i = 0; i < 10; i++)
				{
					help.getline(total, 300);
					if (i == 0)//ù���� continue�� ���ؼ� �����κ��̴� ����� �����ʰ� getline�� �ϰ� ������.
						continue;
					ptr = strtok(total, ",");
					if (command[1] != ptr)
						continue;//�����̸��� �������� ��� �ݺ���������.
					cout << "[COMMAND]" << ptr << endl;//�� �� �տ������� �ϳ��� �߶� ���ڿ��� ����� �ٽ� �޴� �۾��� �������ش�.
					ptr = strtok(NULL, ",");
					cout << "[USAGE]" << ptr << endl;
					ptr = strtok(NULL, ",");
					cout << "[CONDITION]" << ptr << endl;
					ptr = strtok(NULL, ",");
					cout << "[DESCRIPTION]" << ptr << endl;
				}check = 0;
			}
			if (check != 0||command[3]!=" ")//�߸��� �Է��� �ؼ� ������ �ȵ� ���
			{

				for (int i=0;i<10;i++)
				{
					help.getline(total, 300);
					if (i == 0)//ù���� continue�� ���ؼ� �����κ��̴� ����� �����ʰ� getline�� �ϰ� ������.
						continue;
					ptr = strtok(total, ",");
					if (command[0] != ptr)
						continue;//�����̸��� �������� ��� �ݺ���������.
					cout << "Wrong command!" << endl;
					cout << "[COMMAND]" << ptr << endl;//�� �� �տ������� �ϳ��� �߶� ���ڿ��� ����� �ٽ� �޴� �۾��� �������ش�.
					ptr = strtok(NULL, ",");
					cout << "[USAGE]" << ptr << endl;
					ptr = strtok(NULL, ",");
					cout << "[CONDITION]" << ptr << endl;
					ptr = strtok(NULL, ",");
					cout << "[DESCRIPTION]" << ptr << endl;
				}
			}
			help.close();
		}
	}
	return 0;
}
