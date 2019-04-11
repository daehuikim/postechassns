#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Ball.h"
#include "Balloon.h"
#include "Circle.h"
#include "Dot.h"
#include "Drop.h"
#include "DynamicCircle.h"
#include "ppm.h"
#include "frame.h"//기본적으로 필요한 헤더파일을 include시킨다.

using namespace std;

int main()
{
	char word[100];
	int num_Frame(0), num_Circle(0),temp,i(0),type;
	float x, y, rad, vx, vy, vr,R,G,B,A,k;
	ifstream inFile("input.txt");//"input.txt"파일을 읽기위해서
	inFile >> num_Frame;//가장 먼저 처음에 나오는 두 문자를 읽어들여 각각 프레임 갯수와 서클갯수로 지정
	inFile >> num_Circle;
	Circle** arr = new Circle*[num_Circle];
	//첫번째 반복문에서 input.txt파일을 읽어들여서 circlelist에 저장한다.
	while (i<num_Circle)//먼저 원의 갯수만큼의 정보를 읽어들여 circle의 array에 저장한다.
	{
		inFile >> type;//순서대로 읽어드린다. 단, 픽셀 배열 순서를 x,y를 잘못생각해서 다 거꾸로 만들어 놨기 때문에 y,x순서를 바꿔서 읽어야한다. ㅠㅠ(다만들고나서 알았습니다.)
		inFile >> y;
		inFile >> x;
		inFile >> rad;
		inFile >> R;
		inFile >> G;
		inFile >> B;
		inFile >> A;
		inFile >> k;
		inFile >> vx;
		inFile >> vy;
		inFile >> vr;

		if (type == 0)//dot
		{
			Dot* d=new Dot;//각각 읽어들여서 type을 인식하면 type에 맞는 객체를 만들어서 set해주고 그 후 그것을 circle array에 담아준다.
			d->set_type(type);
			d->set_x(x);
			d->set_y(y);
			d->set_ra(rad);
			d->set_color(R);
			d->set_color(G);
			d->set_color(B);
			d->set_color(A);
			d->set_k(k);
			d->set_erase(k);
			arr[i] = (Circle*)d;
		}
		if (type == 1)//drop
		{
			Drop* o=new Drop;//각각 읽어들여서 type을 인식하면 type에 맞는 객체를 만들어서 set해주고 그 후 그것을 circle array에 담아준다.
			o->set_type(type);
			o->set_x(x);
			o->set_y(y);
			o->set_ra(rad);
			o->set_color(R);
			o->set_color(G);
			o->set_color(B);
			o->set_color(A);
			o->set_k(k);
			o->set_gravity(k);
			o->set_vy(vy);
			arr[i] = o;
		}
		if (type == 2)//ball
		{
			Ball* a=new Ball;//각각 읽어들여서 type을 인식하면 type에 맞는 객체를 만들어서 set해주고 그 후 그것을 circle array에 담아준다.
			a->set_type(type);
			a->set_x(x);
			a->set_y(y);
			a->set_ra(rad);
			a->set_color(R);
			a->set_color(G);
			a->set_color(B);
			a->set_color(A);
			a->set_k(k);
			a->set_coeff(k);
			a->set_vx(vx);
			a->set_vy(vy);
			arr[i] = a;
		}
		if (type == 3)//balloon
		{
			Balloon* l=new Balloon;//각각 읽어들여서 type을 인식하면 type에 맞는 객체를 만들어서 set해주고 그 후 그것을 circle array에 담아준다.
			l->set_type(type);
			l->set_x(x);
			l->set_y(y);
			l->set_ra(rad);
			l->set_color(R);
			l->set_color(G);
			l->set_color(B);
			l->set_color(A);
			l->set_k(k);
			l->set_popping(k);
			l->set_vr(vr);
			arr[i] = (Circle*)l;
		}
		i++;
	}
	//두번째 반복문에서 저장된 circlelist들에 있는 애들의 정보를사용한다.
	for (int t=0;t<num_Frame;t++)//먼저 프레임의 갯수만큼 ppm파일을 만들기 위해서 이렇게 해준다.
	{
		Frame* pic = new Frame;

		pic->data = new float**[320];//data를 동적할당하는데,(width,height,color)의 순으로 정보를 담기 위한 동적할당을 한다.

		for (int u = 0; u < 320; u++)
		{
			pic->data[u] = new float *[480];
			for (int v = 0; v < 480; v++)
			{
				pic->data[u][v] = new float[4];
			}
		}
		for (int yy = 0; yy < 320; yy++)//일단모든픽셀들을하얀색으로초기화
		{
			for (int xx = 0; xx < 480; xx++)
			{
				pic->data[yy][xx][0] = 255;
				pic->data[yy][xx][1] = 255;
				pic->data[yy][xx][2] = 255;
				pic->data[yy][xx][3] = 1;
			}
		}
		for (int time = 0; time < num_Circle; time++) //이제 프레임을 만들고 하얀색으로 칠했으니 원 갯수만큼 원을 찍어주면된다.
		{
			int tp;
			float nR, nG, nB, nA;
			
			Circle* ci = new Circle;//원 객체를 하나 선언하여 circle array에 있던 원들을 받아 온다.
			ci = arr[time];
			
			x = ci->get_x();
			y = ci->get_y();
			rad = ci->get_rad();
			tp = ci->get_type();

			if (tp == 0 && t != 0)//그 후 첫 frame은 update를 하지 않고 두번째 frame부터 원 정보를 계속 update해주면서 찍어주기 위해 type에 맞는 객체 생성 후 깊은복사로 다시 배열에담는다.
			{
				Dot* ot = new Dot;
				ot->set_x(ci->get_x());
				ot->set_y(ci->get_y());
				ot->set_ra(ci->get_rad());
				ot->set_color(ci->get_R());
				ot->set_color(ci->get_G());
				ot->set_color(ci->get_B());
				ot->set_color(ci->get_A());
				ot->set_type(ci->get_type());
				ot->set_erase(ci->get_k());
				ot->set_k(ci->get_k());

				arr[time] = (Circle*)ot;
			}
			if (tp == 1&&t!=0)//그 후 첫 frame은 update를 하지 않고 두번째 frame부터 원 정보를 계속 update해주면서 찍어주기 위해 type에 맞는 객체 생성 후 깊은복사로 다시 배열에담는다.
			{
				DynamicCircle* dnc;
				dnc = (DynamicCircle*)arr[time];
				Drop* ro = new Drop;
				ro->set_x(dnc->get_x());
				ro->set_y(dnc->get_y());
				ro->set_ra(dnc->get_rad());
				ro->set_color(dnc->get_R());
				ro->set_color(dnc->get_G());
				ro->set_color(dnc->get_B());
				ro->set_color(dnc->get_A());
				ro->set_type(dnc->get_type());
				ro->set_gravity(dnc->get_k());
				ro->set_k(dnc->get_k());
				ro->set_vy(dnc->get_vy());
				ro->update(ro);
				arr[time] = (Circle*)ro;
			}
			if (tp == 2 && t != 0)//그 후 첫 frame은 update를 하지 않고 두번째 frame부터 원 정보를 계속 update해주면서 찍어주기 위해 type에 맞는 객체 생성 후 깊은복사로 다시 배열에담는다.
			{
				DynamicCircle* dnc = new DynamicCircle;
				dnc = (DynamicCircle*)arr[time];
				Ball* al = new Ball;
				al->set_x(dnc->get_x());
				al->set_y(dnc->get_y());
				al->set_ra(dnc->get_rad());
				al->set_color(dnc->get_R());
				al->set_color(dnc->get_G());
				al->set_color(dnc->get_B());
				al->set_color(dnc->get_A());
				al->set_type(dnc->get_type());
				al->set_coeff(dnc->get_k());
				al->set_k(dnc->get_k());
				al->set_vx(dnc->get_vx());
				al->set_vy(dnc->get_vy());
				if (x + 0.5 - rad < 0 || x + 0.5 + rad>480 || y + 0.5 - rad < 0 || y + 0.5 + rad>320)//경계에 닿는지에 대한 계산
					al->bounce(al);
				al->update(al);
				arr[time] = (Circle*)al;
			}
			if (tp == 3 && t != 0)//그 후 첫 frame은 update를 하지 않고 두번째 frame부터 원 정보를 계속 update해주면서 찍어주기 위해 type에 맞는 객체 생성 후 깊은복사로 다시 배열에담는다.
			{
				DynamicCircle* dnc = new DynamicCircle;
				dnc = (DynamicCircle*)arr[time];
				Balloon* lo = new Balloon;
				lo->set_x(dnc->get_x());
				lo->set_y(dnc->get_y());
				lo->set_ra(dnc->get_rad());
				lo->set_color(dnc->get_R());
				lo->set_color(dnc->get_G());
				lo->set_color(dnc->get_B());
				lo->set_color(dnc->get_A());
				lo->set_type(dnc->get_type());
				lo->set_popping(dnc->get_k());
				lo->set_k(dnc->get_k());
				lo->set_vr(dnc->get_vr());
				if (x + 0.5 - rad < 0 || x + 0.5 + rad>480 || y + 0.5 - rad < 0 || y + 0.5 + rad>320)//경계에 닿는지에 대한 계산
				{
					if (lo->get_popping() == true)
						lo->pop(lo);
				}
				lo->update(lo);
				arr[time] = (Circle*)lo;
			}
			ci = arr[time];//다 담은 후 그 원의 정보를 다시 활용하여 색깔을 칠해준다.
			x = ci->get_x();
			y = ci->get_y();
			rad = ci->get_rad();
			//여기서 해당 픽셀 안에다가 색깔넣어주는거
			for (int gy = 0; gy < 320; gy++)
			{
				for (int gx = 0; gx < 480; gx++)
				{
					if ((gx + 0.5 - x)*(gx + 0.5 - x) + (gy + 0.5 - y)*(gy + 0.5 - y) < rad*rad)//원안에 해당하는픽셀은 RGBA값을 계산하여 칠해준다.
					{
						nR = ci->get_A() * ci->get_R() + pic->data[gy][gx][0] * (1 - ci->get_A());
						nG = ci->get_A() * ci->get_G() + pic->data[gy][gx][1] * (1 - ci->get_A());
						nB = ci->get_A() * ci->get_B() + pic->data[gy][gx][2] * (1 - ci->get_A());
						nA = pic->data[gy][gx][3] + ci->get_A();

						if (pic->data[gy][gx][0] == 0 && pic->data[gy][gx][1]==0 && pic->data[gy][gx][2] == 0 && pic->data[gy][gx][3] == 1)//erase된 부분은 항상 검은색으로
						{
							nR = 0;
							nG = 0;
							nB = 0;
							nA = 1;
						}
						pic->data[gy][gx][0] = nR;
						pic->data[gy][gx][1] = nG;
						pic->data[gy][gx][2] = nB;
						pic->data[gy][gx][3] = nA;

						if (ci->get_type()==0&&ci->get_k()==true)//erase가 true인 점은 항상 검은색으로
						{
							pic->data[gy][gx][0] = 0;
							pic->data[gy][gx][1] = 0;
							pic->data[gy][gx][2] = 0;
							pic->data[gy][gx][3] = 1;
						}
					}
				}
			}
		}
		char pn[100] = "framex.ppm";//그 후파일이름을 지정해주기 위해서 char배열에서 숫자부분만 수정하여서 filename을 넘겨준다.
		pn[5] = t + '0';
		writePPMImage(pic, pn);
		
		for (int u = 0; u < 320; u++)//ppm파일을 생성한 후에는 픽셀에 대한 메모리를 할당해제 해준다.
		{
			for (int v = 0; v < 480; v++)//앞에서 생성할 때와 마찬가지로 3차원 배열이니 한차원마다 할당했듯 한차원마다 해제한다.
			{
				delete[] pic->data[u][v];
			}
		}

		for (int u = 0; u < 320; u++)
		{
			delete[] pic->data[u];
		}
		delete[] pic->data;
	}
	inFile.close();
	return 0;
}