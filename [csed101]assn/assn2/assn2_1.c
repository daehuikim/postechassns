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
	//랜덤함수의 자릿수와 입력받을 것들을 각각 알파벳으로 사용했고(a~h), 사용자가 입력한 값을 put, 그리고 거기에 해당하는 자리들을p(a~h)(put의미) 출력해주는 output자리수를 s(a~h)(show의미)로 했습니다.
	//그리고 답을 맞춘 것인지 틀린 것인지, 재시작여부를 묻는데 필요한 값들을 변수로 지정했다.
	srand(time(NULL));
	trial = 1;
	//랜덤함수를 생성하기 위해 srand(time(NULL))을 적고 trial 값을 1로 초기화함
	while (1) {//while문이 항상 먼저 시작해야해서 1을 적음
		printf("Number Guessing Game!");
		a1 = init_num(a);
		b = a1 / 1000;
		c = a1 % 1000;
		d = c / 100;   //이 구문은 생성된 랜덤생성수의 자릿수를 각각 b d f h에 받는 구문이다.
		e = c % 100;
		f = e / 10;
		g = e % 10;
		h = g / 1;
		//랜덤생성수는 게임한번실행시 고정되어야 함으로 한번만 생성하고 다음 반복문으로 들어간다.
		do {
			printf("\n[Trial %2d ]\n", trial++);
			printf("Input 4 digits <0 to quit> ->");
			scanf("%d", &put);
			if (put != 0 && (put) < 1000 || put > 10000) continue; //입력값이 범위(1000~9999)를 벗어날 시 trial만 증가시키기 위해 continue로 제어했다.
			det = is_correct(put, a1); //is_correct함수를 호출해서 만약 한번에 답을 맞춘지 지속적으로 점검해줄수 있다. 
			if (put == 0) break; //0입력시 게임 포기를 위해 반복문을 탈출하기 위해 break문으로 제어했다.
			pb = put / 1000;
			pc = put % 1000;
			pd = pc / 100;
			pe = pc % 100;  //위에서 랜덤생성수의 자릿수를 받듯 사용자의 입력값을 받는중이다.
			pf = pe / 10;
			pg = pe % 10;
			ph = pg / 1;

			sb = remake_num(b, pb);		//remake_num함수를 호출해서 생성수와 입력값의 자릿수를 비교한다.
			sd = remake_num(d, pd);
			sf = remake_num(f, pf);
			sh = remake_num(h, ph);

			printf("output digits -> %d%d%d%d \n", sb, sd, sf, sh); //재생성된 자릿수(랜덤)을 출력해준다.

		} while (det == 2);

			if (put == 0 && det==2)
			{
				printf("Hmm... You didn't find an answer.\n");//0입력시 출력되는 결과이다.
				printf("Answer is %d \n", a1);
			}
			if (put != 0&&det==1)
			{
				printf("Congratulations! You got a correct answer!\n");
			}//0입력이 아니고 det값이1(맞췄을 때) 나오는 값이다.
			result = is_restart();									//이 때 is_restart함수를 호출해서 재시작 여부를 묻는다.
			trial = 1;			//trial을 다시 초기화 해준다.
			if (result == 1) break;//no(n or N)입력시 종료시키기 위해 break를 통해 제어했다.
		}
	
	return 0;
}
int init_num(int x)
{
	int range;

	range = (9999 - 1000) + 1;//init_num 함수에서는 랜덤함수를 이용해서 1000~9999사이의 랜덤수를 생성한다.
	x = rand() % range + 1000;
	return x;
}
int is_correct(int put, int a1)
{
	if (a1 == put) //입력받은 값과 랜덤생성수를 비교해서 같으면1, 다르면2를 return해주어 정답을 맞춘지 판단해준다.
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

	range = (9 - 0) + 1;  //정답을 못 맞출 경우 자릿수별로 비교하는데, 그 자리에 알맞은 수를 맞춘 경우 그대로 return해주고 아닐경우 생성한 수가 입력받은 값과 원래 정답을 제외하고 생성

	if (b == pb)
	{
		sb = pb;
		return sb;
	}
	else if (b != pb)
	{
		while (sb == pb || sb == b)
		{
			sb = rand() % range; //정답과 입력수를 피하기 위해 반복문의 조건을 통해 계속 생성하기로 함
		}
		return sb;
	}
}
int is_restart()
{
	char check;  //이 함수에서 재시작 여부를 물어보고 예외처리를 하기 위해 0과 1로만 return해서 재시작 여부를 물을 수 있음.


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