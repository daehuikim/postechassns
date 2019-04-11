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

	SVGObject* root = new SVGObject;//처음 root를 담기위한 동적할당
	Selection* selecti = new Selection;//selectionlist에 넣어줄 selection들 할당
	SelectionList* sl = new SelectionList;//selection명령어의 결과물을 담을 selectionlist
	SVGObject* pselect = new SVGObject;//현재 셀렉션을 받을 pselect라는 svgobject선언
	SVGObjectList* pList = new SVGObjectList;
	root->SetTagName("HTML");//프로그램실행시 root selection을 생성한다.
	pselect = root;
	selecti->SetsvgObject(pselect);
	sl->AddSelection(selecti);//그 후 root를 셀렉트한다.

	while (1)
	{
		cout << "<SVGmaker>";//명령어를 입력받는 부분이다.
		getline(cin, m);
		stringstream ss(m);
		string temp, numstring;
		int i = 0,check=0;//check값에 변동을 주어 명령어 수행여부를 조사한다.
		command[0] = " ", command[1] = " ", command[2] = " ",command[3]=" ", num = 0;//모든 명령어에 대한 예외처리를 위해서 항상 초기화를 함.
		while (ss >> temp)//string stream을 이용해서 space를 기준으로 parsing
		{
			if (i < 2)//맨 처음 두가지 명령어를 command에 받는다.
				command[i] = temp;
			if (i == 2)
			{
				command[2] = temp;
				numstring = command[2];//string으로 하나받는다.
			}
			if (i == 3)
				command[3] = temp;
			i++;
		}

		if (command[0] == "append")
		{
			check = 1;//append가 수행되었는지 확인하는거
			if (numstring.size() != 0)//위에서 받은 string형을 계산하기 위해 int로 바꿔준다.
				num = stoi(numstring);
			Selection* one = new Selection;
			one = sl->GetHead();
			if (num == 0)
				num = 1;
			sl->Clear();//항상 어펜드하기전에는 현재 셀렉션 리스트를 비워주고 새로 어펜드 된 객체를 셀렉트하도록 selection이동에 유의한다.
			for (i = 0; i < num; i++)
			{
				if (command[3] != " ")
				{
					sl->AddSelection(one);
					break;
				}
				if (one->GetsvgObject()->Getchildlist() == NULL)//만약 childlist가 없는 경우, 즉 이전에 형제가 없던 경우는 list를 생성하고 있던 경우에는 생성하지않고 그 뒤에 이어단다.
				{
					SVGObjectList* cl = new SVGObjectList;
					one->GetsvgObject()->SetChildlist(cl);
				}
				SVGObject* SVG = new SVGObject;//append하기 위해 새로운 객체를 생성해주고 selection도 할당한다.
				Selection* SEL = new Selection;
				SVG->SetTagName(command[1]);
				SVG->SetParent(one->GetsvgObject());
				one->GetsvgObject()->Getchildlist()->AddSvgObject(SVG);//명령한 정보를 토대로 childlist와 selectionlist에 넣는 수행을 해준다.
				SEL->SetsvgObject(SVG);
				sl->AddSelection(SEL);
				check = 0;
			}
		}
		if (command[0] == "select")
		{
			check = 2;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			int m(0);
			string tgnm;
			SVGObject* dam = new SVGObject;//처음에 이전 셀렉션에 대한 정보를 dam을(담을) dam을 생성
			SVGObject* par = new SVGObject;//이전 셀렉션이 부모가 되므로 par(패런츠의미) 생성해서 dam을 우선 저장해둔다.

			dam = sl->GetHead()->GetsvgObject();
			par = dam;
			if (numstring.size() != 0)//append때와 마찬가지로숫자를 int로 받아서 계산해둔다.
				num = stoi(numstring);
			if (sl->GetSize() > 1 && command[1] != " ")//multiple-selection일때는 select가 안되도록 한다.
			{
				cout << "Wrong Command!" << endl;
				m = 1;//m값을 변화시켜주어 잘못 입력시 뒷 수행을 안하도록 한다.
			}
			if (command[1] == " "&&m == 0)//그냥 select만 입력했을 경우 현재의 트리를 보여주도록 설정
			{
				sl->PrintList(root);
				continue;
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			}

			sl->Clear();//셀렉트를 하기 위해 아까 dam에 현재 셀렉트 정보를 저장후 셀렉션을 비워준다.
			if (command[1] != " "&&num == 0)//특정이름의 객체를 모두 셀렉트할 경우의 반복문
			{
				int a = 0;//a값 변화를 기준으로 select된 여부를 알려줌. 즉,자식이 없을 경우의 예외처리
				for (SVGObject* temp = par->GetFirstChild(); temp != NULL; temp = temp->GetNext())//temp라는 검색용 객체주소를 이용한다.
				{
					if (temp->GetTagName() == command[1])//명령받은 단어와 이름이 같은 경우 셀렉션에 추가해준다.
					{
						Selection* tong = new Selection;
						tong->SetsvgObject(temp);
						sl->AddSelection(tong);
						a = 1;
					}
				}if (a == 0)//만약 셀렉션에 아무것도 추가되지 않았으면 원래 셀렉션을 가르킨다.
				{
					cout << "Wrong Command! 자식이 없습니다." << endl;
					Selection* tong = new Selection;
					tong->SetsvgObject(par);//원래셀렉션을 위해 par사용
					sl->AddSelection(tong);
					cout << "selection is not changed." << endl;
				}
				cout << sl->GetSize() << "item(s) is selected!" << endl;//selection이 끝난 후 몇개가 셀렉트 되었는지 출력
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			}
			else if (command[1] != " "&&num != 0)//특정 index의 하나를 select하는 경우의 반복문이다. 내용은 위와 똑같다.
			{
				int a = 0, b = 0;//a로 현재 childlist들의 순번을 check해주고 b로는 셀렉트 여부를 체크한다.
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
				}if (b == 0)//아까와 마찬가지로 셀렉트 된 객체가 없을 경우 원래 셀렉션을 가르킨다.
				{
					Selection* tong = new Selection;
					tong->SetsvgObject(par);
					sl->AddSelection(tong);
					cout << "selection is not changed." << endl;
				}
				cout << sl->GetSize() << "item(s) is selected!" << endl;//하나만 선택된 것을 알려준다.
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			}
		}
		if (command[0] == "remove")
		{
			check = 3;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			SVGObject* ro = new SVGObject;//remove하기 위해 받아놓을 객체와 부모객체를 생성한다.
			SVGObject* p = new SVGObject;
			Selection* ra = new Selection;//remove한 후 새로운 selectionlist에 넣어줄 selection생성
			ro = sl->GetHead()->GetsvgObject();
			p = ro->GetParent();
			if (ro->GetParent() == NULL)//parent는 remove하지 못하게 한다.
			{
				cout << "Error! Wrong Command" << endl;
			}

			else
			{
				ro = p->GetFirstChild();//선언부에서 p에 현재 셀렉션 된 객체의 부모노드를 받아놓고 ro에 그 자식을 넣어 처음부터 돌린다.
				for (Selection* temp = sl->GetHead(); temp != NULL;)
				{
					if (ro->GetNext() == temp->GetsvgObject())//현재 셀렉션된 객체를 찾기위해 ro와 select된 객체를 비교하여 같으면 remove한다.
					{
						ro->SetNext(ro->GetNext()->GetNext());//삭제하기전 next노드를 연결해준다.
						sl->RemoveSelection(temp);//selection list에서도 리무브하면서 동시에 객체를 삭제한다.
						temp = temp->GetNext();
					}
					ro = ro->GetNext();//만약 삭제를 안하면 다음 노드로 검색을 지속한다.
				}
				sl->Clear();//삭제한 후 셀렉션 리스트를 비우고 맨처음 받아놨던 부모객체를 셀렉트하여 셀렉션이동을마무리
				ra->SetsvgObject(p);
				sl->AddSelection(ra);
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			}
		}
		if (command[0] == "end")
		{
			check = 4;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			SVGObject *pa = new SVGObject;
			Selection* se = new Selection;

			pa = sl->GetHead()->GetsvgObject();//pa에 현재 셀렉션리스트의 헤드를 넣어준다.

			if (command[1] == " ")
			{
				if (pa == root)
					cout << "Error! Wrong Command" << endl;//현재 root노드를 가지고 있을 경우 에러나게 출력
				else
				{
					sl->Clear();//현재 셀렉션 리스트를 비우고 처음 받아놨던 부모노드를 셀렉션에 채움으로 셀렉션 이동 완료
					pa = pa->GetParent();//selection을 부모로이동시켜준다.
					se->SetsvgObject(pa);
					sl->AddSelection(se);
				}
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			}
			//추가구현 기능 ****************root end****************************
			else if (command[1] == "root")
			{
				if (pa == root)
					cout << "It's already root!" << endl;//root일경우에는 error출력
				else
				{
					while (pa != root)//반복문으로 root가 나올때까지 계속 실행한다.
					{
						sl->Clear();//현재 셀렉션 리스트를 비우고 처음 받아놨던 부모노드를 셀렉션에 채움으로 셀렉션 이동 완료
						pa = pa->GetParent();//selection을 부모로이동시켜준다.
						se->SetsvgObject(pa);
						sl->AddSelection(se);
					}cout << "Now root is selected!" << endl;//root node가 선택됨을 알려줌
					check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
				}
			}
			else if (command[1] != "root"&&command[1] != " ")//이미 루트 노드 일 경우 해당 구현기능을 실행하지 않고 에러문 출력
			{
				cout << "You should enter 'root' or nothing." << endl;
			}
		}
		if (command[0] == "exit")
		{
			break;//exit을 입력 시 while문을 빠져나가면서 프로그램 종료
		}
		if (command[0] == "cattr")
		{
			check = 6;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			Selection* bs; //받는 셀렉션 Bat neon Selection의 앞글자(죄송합니다 변수이름이 더이상 생각안나서요..)
			SVGObject* sb;//셀렉션변수이름을 반대로 한 오브젝트변수 선언
			int attSize(1), i, slSize;
			bs = sl->GetHead();//현재selection의 head를 준다.
			slSize = sl->GetSize();//현재 셀렉션리스트의 수
			for (i = 0; i < slSize; i++)//셀렉션리스트의 숫자만큼 반복문을 돈다.
			{
				sb = bs->GetsvgObject();
				if (sb->GetAttributeList() == NULL) {//만약 attribute가 하나도 없는 상태이면 list를 생성해서 추가해준다.
					SVGAttributeList* al = new SVGAttributeList;
					sb->SetAttributeList(al);
				}
				attSize = sb->GetAttributeList()->GetSize();
				SVGAttribute* pSelectAtt = new SVGAttribute;//추가용 attribute생성
				pSelectAtt->SetName(command[1]);
				pSelectAtt->SetValue(numstring);
				int y = 0;
				for (SVGAttribute* temp = sb->GetAttributeList()->GetHead(); temp != NULL; temp = temp->GetNext())//만약 이미 attribute가 있을 경우 이름을 바꾸거나 추가해주기 위해 전체 attributelist를 검색한다.
				{
					if (temp->GetName() == command[1])//같은이름의 attribute는 값만바꿈
					{
						temp->SetValue(numstring);//값만바꾸어준다.
						y = 1;//값을 바꾼 후 만약 다른 attribute와 이름 비교 후 이름이 달라서 또 추가할까봐 y값을 변경시킴으로 새로운 노드를 추가하지 않아도 되는 것을 알려줌
					}
				}
				if (y == 0)
				{
					sb->GetAttributeList()->AddSvgAttribute(pSelectAtt);//새로운 Attribute추가
				}
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
				if (bs->GetNext() == NULL)
					break;//마지막노드는제외
				bs = bs->GetNext();//다음셀렉션으로검색
			}
		}
		if (command[0] == "tattr")
		{
			check = 7;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			if (numstring.size() != 0)//numstring을 int로변환시켜준다.
				num = stoi(numstring);
			float n1(0), n2(0);
			string f1, f2;
			f1 = to_string(n1), f2 = to_string(n2);//float형을 string으로 출력해야 하기 때문에 string형도 생성한다.
			Selection* bs;//이하 노드 삽입 내용은 cattr과 동일하게 되어있다.
			SVGObject* sb;
			int attSize(1), i, slSize;

			bs = sl->GetHead();//현재selection의 hea
			slSize = sl->GetSize();//현재 셀렉션리스트의 수
			for (i = 0; i < slSize; i++)
			{
				sb = bs->GetsvgObject();
				if (sb->GetAttributeList() == NULL) {//만약 attribute가 하나도 없는 상태이면 list를 생성해서 추가해준다.
					SVGAttributeList* al = new SVGAttributeList;
					sb->SetAttributeList(al);
				}
				attSize = sb->GetAttributeList()->GetSize();
				SVGAttribute* pSelectAtt = new SVGAttribute;//추가용 attribute생성
				pSelectAtt->SetName("transform");//tattr의 경우 특정한 이름과 값의 형이 있으므로 지정해준다.
				pSelectAtt->SetValue("translate(" + f1 + "," + f2 + ")");//이런 형식으로 string을 붙여서 출력해준다. 처음에는f1,f2값을 0으로 선언부에서 초기화했다.
				int y = 0;
				for (SVGAttribute* temp = sb->GetAttributeList()->GetHead(); temp != NULL; temp = temp->GetNext())//만약 이미 attribute가 있을 경우 이름을 바꾸거나 추가해주기 위해 전체 attributelist를 검색한다.
				{

					if (temp->GetName() == command[1])//같은이름의 attribute는 값만바꿈
					{
						temp->SetValue(numstring);//값만바꾸어준다.
						y = 1;//값을 바꾼 후 만약 다른 attribute와 이름 비교 후 이름이 달라서 또 추가할까봐 y값을 변경시킴으로 새로운 노드를 추가하지 않아도 되는 것을 알려줌
					}
				}
				if (y == 0)
				{
					sb->GetAttributeList()->AddSvgAttribute(pSelectAtt);//새로운 Attribute추가
				}
				n1 = n1 + stoi(command[1]), n2 = n2 + num;//입력한 값의 숫자 만큼 증가시켜주는 구문이다.
				f1 = to_string(n1), f2 = to_string(n2);
				if (bs->GetNext() == NULL)
					break;//마지막노드는제외
				bs = bs->GetNext();//다음셀렉션으로검색
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			}
		}
		if (command[0] == "print")
		{
			check = 8;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			if (command[1] == " ")
			{
				sl->PrintListw(root);//만약 그냥 print만 출력하면 *을 제외하여 리스트를 출력시켜주도록 하는 함수를 호출한다.
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			}
			else//파일 이름을 입력하면 해당파일명을 가진 파일로 출력하게 해준다.
			{
				string filename;
				filename = command[1];
				ofstream File;
				File.open(filename);
				sl->PrintListf(root, File);
				File.close();
				cout << "\"" << filename << "\"" << "file is created" << endl;
				check = 0;//check값에 변화를 주어 잘못입력될 경우를 잡아냄
			}
		}
		if (command[0] == "help"||check!=0)//잘못된 명령어를 넣어 수행안될 경우도 시행되어야 하므로check조건도 삽입
		{
			check = 9;
			ifstream help;
			string com, use, condition, des, tem, nm;//명령어들을 받아 놓을 string들 선언
			char total[300];//strtok함수를 사용하기 위한 char와 char포인터를 생성한다.
			char* ptr, *context = NULL;
			int p(0);
			help.open("help.csv");
			if (command[1] == " ") {//그냥 help만 입력할 경우 getline으로 한 줄을 채로 받은 후 ,를 기준으로 자른다.
				for (int i = 0; i < 10; i++)
				{
					help.getline(total, 300);
					if (i == 0)
						continue;
					ptr = strtok(total, ",");//첫번째는 name부분이니 자른 후 아무 처리를 하지 않는다.
					ptr = strtok(NULL, ",");//두번째에 usage가 들어있으므로 이를 반복문으로 프린트해준다.
					cout << ptr << endl;
					check = 0;
				}
			}
			if (command[1] != " "&&check != 0&&command[0]=="help")//만약 특정 명령어가 있는 명령을 받을 경우는 한가지의 모든 영역을 출력해준다.
			{
				for (int i = 0; i < 10; i++)
				{
					help.getline(total, 300);
					if (i == 0)//첫줄은 continue를 통해서 목차부분이니 출력은 하지않고 getline만 하고 버린다.
						continue;
					ptr = strtok(total, ",");
					if (command[1] != ptr)
						continue;//같은이름이 없으면은 계속 반복문을돈다.
					cout << "[COMMAND]" << ptr << endl;//그 후 앞에서부터 하나씩 잘라낸 문자열을 출력후 다시 받는 작업을 지속해준다.
					ptr = strtok(NULL, ",");
					cout << "[USAGE]" << ptr << endl;
					ptr = strtok(NULL, ",");
					cout << "[CONDITION]" << ptr << endl;
					ptr = strtok(NULL, ",");
					cout << "[DESCRIPTION]" << ptr << endl;
				}check = 0;
			}
			if (check != 0||command[3]!=" ")//잘못된 입력을 해서 수행이 안된 경우
			{

				for (int i=0;i<10;i++)
				{
					help.getline(total, 300);
					if (i == 0)//첫줄은 continue를 통해서 목차부분이니 출력은 하지않고 getline만 하고 버린다.
						continue;
					ptr = strtok(total, ",");
					if (command[0] != ptr)
						continue;//같은이름이 없으면은 계속 반복문을돈다.
					cout << "Wrong command!" << endl;
					cout << "[COMMAND]" << ptr << endl;//그 후 앞에서부터 하나씩 잘라낸 문자열을 출력후 다시 받는 작업을 지속해준다.
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
