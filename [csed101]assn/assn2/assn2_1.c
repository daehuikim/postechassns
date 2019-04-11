#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int init_num(int x);
int is_correct(int, int);
int remake_num(int, int);
int is_restart();

int main()
{
	int a1 = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, pb = 0, pc = 0, pd = 0, pe = 0, pf = 0, pg = 0, ph = 0, sb = 0, sd = 0, sf = 0, sh = 0, result = 0, trial, put = -1, det = 2;
	//�����Լ��� �ڸ����� �Է¹��� �͵��� ���� ���ĺ����� ����߰�(a~h), ����ڰ� �Է��� ���� put, �׸��� �ű⿡ �ش��ϴ� �ڸ�����p(a~h)(put�ǹ�) ������ִ� output�ڸ����� s(a~h)(show�ǹ�)�� �߽��ϴ�.
	//�׸��� ���� ���� ������ Ʋ�� ������, ����ۿ��θ� ���µ� �ʿ��� ������ ������ �����ߴ�.
	srand(time(NULL));
	trial = 1;
	//�����Լ��� �����ϱ� ���� srand(time(NULL))�� ���� trial ���� 1�� �ʱ�ȭ��
	while (1) {//while���� �׻� ���� �����ؾ��ؼ� 1�� ����
		printf("Number Guessing Game!");
		a1 = init_num(a);
		b = a1 / 1000;
		c = a1 % 1000;
		d = c / 100;   //�� ������ ������ ������������ �ڸ����� ���� b d f h�� �޴� �����̴�.
		e = c % 100;
		f = e / 10;
		g = e % 10;
		h = g / 1;
		//������������ �����ѹ������ �����Ǿ�� ������ �ѹ��� �����ϰ� ���� �ݺ������� ����.
		do {
			printf("\n[Trial %2d ]\n", trial++);
			printf("Input 4 digits <0 to quit> ->");
			scanf("%d", &put);
			if (put != 0 && (put) < 1000 || put > 10000) continue; //�Է°��� ����(1000~9999)�� ��� �� trial�� ������Ű�� ���� continue�� �����ߴ�.
			det = is_correct(put, a1); //is_correct�Լ��� ȣ���ؼ� ���� �ѹ��� ���� ������ ���������� �������ټ� �ִ�. 
			if (put == 0) break; //0�Է½� ���� ���⸦ ���� �ݺ����� Ż���ϱ� ���� break������ �����ߴ�.
			pb = put / 1000;
			pc = put % 1000;
			pd = pc / 100;
			pe = pc % 100;  //������ ������������ �ڸ����� �޵� ������� �Է°��� �޴����̴�.
			pf = pe / 10;
			pg = pe % 10;
			ph = pg / 1;

			sb = remake_num(b, pb);		//remake_num�Լ��� ȣ���ؼ� �������� �Է°��� �ڸ����� ���Ѵ�.
			sd = remake_num(d, pd);
			sf = remake_num(f, pf);
			sh = remake_num(h, ph);

			printf("output digits -> %d%d%d%d \n", sb, sd, sf, sh); //������� �ڸ���(����)�� ������ش�.

		} while (det == 2);

			if (put == 0 && det==2)
			{
				printf("Hmm... You didn't find an answer.\n");//0�Է½� ��µǴ� ����̴�.
				printf("Answer is %d \n", a1);
			}
			if (put != 0&&det==1)
			{
				printf("Congratulations! You got a correct answer!\n");
			}//0�Է��� �ƴϰ� det����1(������ ��) ������ ���̴�.
			result = is_restart();									//�� �� is_restart�Լ��� ȣ���ؼ� ����� ���θ� ���´�.
			trial = 1;			//trial�� �ٽ� �ʱ�ȭ ���ش�.
			if (result == 1) break;//no(n or N)�Է½� �����Ű�� ���� break�� ���� �����ߴ�.
		}
	
	return 0;
}
int init_num(int x)
{
	int range;

	range = (9999 - 1000) + 1;//init_num �Լ������� �����Լ��� �̿��ؼ� 1000~9999������ �������� �����Ѵ�.
	x = rand() % range + 1000;
	return x;
}
int is_correct(int put, int a1)
{
	if (a1 == put) //�Է¹��� ���� ������������ ���ؼ� ������1, �ٸ���2�� return���־� ������ ������ �Ǵ����ش�.
	{
		return 1;
	}
	else
	{
		return 2;
	}

}
int remake_num(int b, int pb)
{
	int sb = b;
	int range;

	range = (9 - 0) + 1;  //������ �� ���� ��� �ڸ������� ���ϴµ�, �� �ڸ��� �˸��� ���� ���� ��� �״�� return���ְ� �ƴҰ�� ������ ���� �Է¹��� ���� ���� ������ �����ϰ� ����

	if (b == pb)
	{
		sb = pb;
		return sb;
	}
	else if (b != pb)
	{
		while (sb == pb || sb == b)
		{
			sb = rand() % range; //����� �Է¼��� ���ϱ� ���� �ݺ����� ������ ���� ��� �����ϱ�� ��
		}
		return sb;
	}
}
int is_restart()
{
	char check;  //�� �Լ����� ����� ���θ� ����� ����ó���� �ϱ� ���� 0�� 1�θ� return�ؼ� ����� ���θ� ���� �� ����.


	while (1)
	{
		getchar();
		printf("Try again <y/n> -> ");
		scanf("%c", &check);

		if (check == 'y' || check == 'Y')
		{
			return 0;
		}
		else if (check == 'n' || check == 'N')
		{
			return 1;
		}
	}
}