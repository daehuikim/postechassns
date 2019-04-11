#include "assn5.h"//헤더를 인클루드한다.
void print_game(LIST *d, LIST *p, int sum_d, int sum_p, int money, int pro, int tp)
{
	int i, j, k, l;
	NODE *temp;
	system("cls");//항상 cls로 앞의 print된 게임을 없애준다.
	printf("[소지금 : %d] [배팅금액: %d]\n", money, pro);
	printf("-----------------------------------------\n");
	printf("<Dealer> ");

	if (tp != 2)//플레이어 턴일 동안은 첫카드를 공개하지 않는다.
		printf("[????] ");

	else if (tp == 2)
	{
		temp = d->head;
		if (temp->data.numb > 58)//numb가 char형이기 때문에 아스키 코드값이 숫자 보다 큰 대문자일 경우 %c로 출력, 숫자일 경우에는 %d로 출력해준다(아래도 다 이렇게함)
		{
			printf("[%s %c]", d->head->data.shape, d->head->data.numb);
		}
		else if (temp->data.numb <= 58)
		{
			printf("[%s %d] ", temp->data.shape, temp->data.numb);
		}
	}
	temp = d->head->next;
	for (i = 0; i < d->count - 1; i++)
	{
		if (temp->data.numb > 58)
		{
			printf("[%s %c] ", temp->data.shape, temp->data.numb);
			temp = temp->next;
		}
		else if (temp->data.numb <= 58)
		{
			printf("[%s %d] ", temp->data.shape, temp->data.numb);
			temp = temp->next;
		}
	}
	k = d->head->data.numb;//받은 카드에 대한 숫자 판별처리이고 합을 바꿔준다.
	k = is_numb(k);
	k = is_A(k, sum_d);
	if (tp != 2)
	{
		if (k == 1)
			k = 11;
		printf(", Sum=%d\n", sum_d - k);//첫번째 장 정보를 없애기 위해 k값을 없애고 출력해준다.
	}
	if (tp == 2)
		printf(", Sum=%d\n", sum_d);//만약 딜러턴일 때는 첫번째카드까지 더해서 합을 출력해준다.
	printf("<Player> ");//플레이어의 카드는 위와같은 메커니즘으로 출력
	temp = p->head;
	for (j = 0; j < p->count; j++)
	{
		if (temp->data.numb > 58)
		{
			printf("[%s %c] ", temp->data.shape, temp->data.numb);
		}
		else if (temp->data.numb <= 58)
		{
			printf("[%s %d] ", temp->data.shape, temp->data.numb);
		}
		temp = temp->next;
	}
	printf(", Sum=%d\n", sum_p);
	printf("\n");
}
int is_numb(int a)
{
	if (a == 74 || a == 75 || a == 81)//A가 아닌 JKQ일때 10으로 지정해주고
		a = 10;
	else if (a == 65)//A일때는 우선 0을 return한다.
		a = 0;
	else
		return a;
	return a;
}
int is_A(int a, int sum)
{
	if (a == 0)//만약 A일경우 0이 리턴되었기 때문에 여기서 합의 크기를 보고 판별해준다.
	{
		if (sum > 10)
			a = 1;
		else if (sum <= 10)
			a = 11;
	}
	else
		return a;
	return a;
}
