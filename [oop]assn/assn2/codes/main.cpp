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
#include "frame.h"//�⺻������ �ʿ��� ��������� include��Ų��.

using namespace std;

int main()
{
	char word[100];
	int num_Frame(0), num_Circle(0),temp,i(0),type;
	float x, y, rad, vx, vy, vr,R,G,B,A,k;
	ifstream inFile("input.txt");//"input.txt"������ �б����ؼ�
	inFile >> num_Frame;//���� ���� ó���� ������ �� ���ڸ� �о�鿩 ���� ������ ������ ��Ŭ������ ����
	inFile >> num_Circle;
	Circle** arr = new Circle*[num_Circle];
	//ù��° �ݺ������� input.txt������ �о�鿩�� circlelist�� �����Ѵ�.
	while (i<num_Circle)//���� ���� ������ŭ�� ������ �о�鿩 circle�� array�� �����Ѵ�.
	{
		inFile >> type;//������� �о�帰��. ��, �ȼ� �迭 ������ x,y�� �߸������ؼ� �� �Ųٷ� ����� ���� ������ y,x������ �ٲ㼭 �о���Ѵ�. �Ф�(�ٸ������ �˾ҽ��ϴ�.)
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
			Dot* d=new Dot;//���� �о�鿩�� type�� �ν��ϸ� type�� �´� ��ü�� ���� set���ְ� �� �� �װ��� circle array�� ����ش�.
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
			Drop* o=new Drop;//���� �о�鿩�� type�� �ν��ϸ� type�� �´� ��ü�� ���� set���ְ� �� �� �װ��� circle array�� ����ش�.
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
			Ball* a=new Ball;//���� �о�鿩�� type�� �ν��ϸ� type�� �´� ��ü�� ���� set���ְ� �� �� �װ��� circle array�� ����ش�.
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
			Balloon* l=new Balloon;//���� �о�鿩�� type�� �ν��ϸ� type�� �´� ��ü�� ���� set���ְ� �� �� �װ��� circle array�� ����ش�.
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
	//�ι�° �ݺ������� ����� circlelist�鿡 �ִ� �ֵ��� ����������Ѵ�.
	for (int t=0;t<num_Frame;t++)//���� �������� ������ŭ ppm������ ����� ���ؼ� �̷��� ���ش�.
	{
		Frame* pic = new Frame;

		pic->data = new float**[320];//data�� �����Ҵ��ϴµ�,(width,height,color)�� ������ ������ ��� ���� �����Ҵ��� �Ѵ�.

		for (int u = 0; u < 320; u++)
		{
			pic->data[u] = new float *[480];
			for (int v = 0; v < 480; v++)
			{
				pic->data[u][v] = new float[4];
			}
		}
		for (int yy = 0; yy < 320; yy++)//�ϴܸ���ȼ������Ͼ�������ʱ�ȭ
		{
			for (int xx = 0; xx < 480; xx++)
			{
				pic->data[yy][xx][0] = 255;
				pic->data[yy][xx][1] = 255;
				pic->data[yy][xx][2] = 255;
				pic->data[yy][xx][3] = 1;
			}
		}
		for (int time = 0; time < num_Circle; time++) //���� �������� ����� �Ͼ������ ĥ������ �� ������ŭ ���� ����ָ�ȴ�.
		{
			int tp;
			float nR, nG, nB, nA;
			
			Circle* ci = new Circle;//�� ��ü�� �ϳ� �����Ͽ� circle array�� �ִ� ������ �޾� �´�.
			ci = arr[time];
			
			x = ci->get_x();
			y = ci->get_y();
			rad = ci->get_rad();
			tp = ci->get_type();

			if (tp == 0 && t != 0)//�� �� ù frame�� update�� ���� �ʰ� �ι�° frame���� �� ������ ��� update���ָ鼭 ����ֱ� ���� type�� �´� ��ü ���� �� ��������� �ٽ� �迭����´�.
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
			if (tp == 1&&t!=0)//�� �� ù frame�� update�� ���� �ʰ� �ι�° frame���� �� ������ ��� update���ָ鼭 ����ֱ� ���� type�� �´� ��ü ���� �� ��������� �ٽ� �迭����´�.
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
			if (tp == 2 && t != 0)//�� �� ù frame�� update�� ���� �ʰ� �ι�° frame���� �� ������ ��� update���ָ鼭 ����ֱ� ���� type�� �´� ��ü ���� �� ��������� �ٽ� �迭����´�.
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
				if (x + 0.5 - rad < 0 || x + 0.5 + rad>480 || y + 0.5 - rad < 0 || y + 0.5 + rad>320)//��迡 ������� ���� ���
					al->bounce(al);
				al->update(al);
				arr[time] = (Circle*)al;
			}
			if (tp == 3 && t != 0)//�� �� ù frame�� update�� ���� �ʰ� �ι�° frame���� �� ������ ��� update���ָ鼭 ����ֱ� ���� type�� �´� ��ü ���� �� ��������� �ٽ� �迭����´�.
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
				if (x + 0.5 - rad < 0 || x + 0.5 + rad>480 || y + 0.5 - rad < 0 || y + 0.5 + rad>320)//��迡 ������� ���� ���
				{
					if (lo->get_popping() == true)
						lo->pop(lo);
				}
				lo->update(lo);
				arr[time] = (Circle*)lo;
			}
			ci = arr[time];//�� ���� �� �� ���� ������ �ٽ� Ȱ���Ͽ� ������ ĥ���ش�.
			x = ci->get_x();
			y = ci->get_y();
			rad = ci->get_rad();
			//���⼭ �ش� �ȼ� �ȿ��ٰ� ����־��ִ°�
			for (int gy = 0; gy < 320; gy++)
			{
				for (int gx = 0; gx < 480; gx++)
				{
					if ((gx + 0.5 - x)*(gx + 0.5 - x) + (gy + 0.5 - y)*(gy + 0.5 - y) < rad*rad)//���ȿ� �ش��ϴ��ȼ��� RGBA���� ����Ͽ� ĥ���ش�.
					{
						nR = ci->get_A() * ci->get_R() + pic->data[gy][gx][0] * (1 - ci->get_A());
						nG = ci->get_A() * ci->get_G() + pic->data[gy][gx][1] * (1 - ci->get_A());
						nB = ci->get_A() * ci->get_B() + pic->data[gy][gx][2] * (1 - ci->get_A());
						nA = pic->data[gy][gx][3] + ci->get_A();

						if (pic->data[gy][gx][0] == 0 && pic->data[gy][gx][1]==0 && pic->data[gy][gx][2] == 0 && pic->data[gy][gx][3] == 1)//erase�� �κ��� �׻� ����������
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

						if (ci->get_type()==0&&ci->get_k()==true)//erase�� true�� ���� �׻� ����������
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
		char pn[100] = "framex.ppm";//�� �������̸��� �������ֱ� ���ؼ� char�迭���� ���ںκи� �����Ͽ��� filename�� �Ѱ��ش�.
		pn[5] = t + '0';
		writePPMImage(pic, pn);
		
		for (int u = 0; u < 320; u++)//ppm������ ������ �Ŀ��� �ȼ��� ���� �޸𸮸� �Ҵ����� ���ش�.
		{
			for (int v = 0; v < 480; v++)//�տ��� ������ ���� ���������� 3���� �迭�̴� ���������� �Ҵ��ߵ� ���������� �����Ѵ�.
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