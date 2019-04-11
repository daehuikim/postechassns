#include "assn5.h"
#include <stdio.h>//NULL문자 사용을 위해 인클루드함.
int bet(int money, int o_money)//베팅과정을 포함하는 함수이다.
{
	int betmoney;
	if (money > o_money * 100)//예외처리이다
	{
		printf("당신은 돈을 너무 많이 벌어 카지노 업체가 당신을 쫓아냈습니다!\n");
		printf("카지노에서 $%d로 무려 $%d를 벌었습니다!!!\n", o_money, money);
		return 0;
	}
	if (money == 0)//예외처리
	{
		printf("재산이 없어서 카지노에서 쫓겨났습니다...\n");
		printf("역시 올인은 하면 안돼요...\n");
		return 0;
	}

	while (1)//유효한 금액을 입력할 때까지 입력받게 함.
	{
		printf("[현재 소지금: $%d] 배팅 금액을 설정하세요! <0 for Exit>", money);
		scanf("%d", &betmoney);

		if (betmoney<0 || betmoney>money)
		{
			printf("유효한 배팅금액을 설정해주세요!\n");
		}
		else
			break;
	}

	if (betmoney == 0)//프로그램 종료시에 출력해주는 함수이다.
	{
		printf("당신은 $%d을 들고가서 $%d를 남겨왔습니다.\n", o_money, money);
		return 0;
	}

	return betmoney;
}
void insert_node(LIST *plist, int t)
{
	NODE *NEW;//NODE를 생성해서 삽입하기 위해 NEW라는 노드 할당 후 각각 plist에 대입해준다.

	NEW = (NODE*)malloc(sizeof(NODE));
	NEW->next = NULL;
	add_card(&NEW->data, t);

	if (plist->head == NULL)
		plist->head = NEW;
	else
		plist->tail->next = NEW;

	plist->tail = NEW;
	plist->count++;
}
void add_card(CARD *s, int t)
{
	if (t >= 0 && t < 13)//카드를 순서대로 받아준다.
	{
		s->shape = "♠";
		s->numb = t + 2;

		if (t == 9)
			s->numb = 'A';
		else if (t == 10)
			s->numb = 'J';
		else if (t == 11)
			s->numb = 'Q';
		else if (t == 12)
			s->numb = 'K';
	}
	else if (t >= 13 && t < 26)
	{
		s->shape = "♥";
		s->numb = t - 13 + 2;

		if (t == 22)
			s->numb = 'A';
		else if (t == 23)
			s->numb = 'J';
		else if (t == 24)
			s->numb = 'Q';
		else if (t == 25)
			s->numb = 'K';
	}
	else if (t >= 26 && t < 39)
	{
		s->shape = "◆";
		s->numb = t - 26 + 2;

		if (t == 35)
			s->numb = 'A';
		else if (t == 36)
			s->numb = 'J';
		else if (t == 37)
			s->numb = 'Q';
		else if (t == 38)
			s->numb = 'K';
	}
	else if (t >= 39 && t < 52)
	{
		s->shape = "♣";
		s->numb = t - 39 + 2;

		if (t == 48)
			s->numb = 'A';
		else if (t == 49)
			s->numb = 'J';
		else if (t == 50)
			s->numb = 'Q';
		else if (t == 51)
			s->numb = 'K';
	}

}
void shuffle_card(LIST *s)
{
	int i, j, k;
	CARD tmp, tmp1;
	NODE *temp;

	for (i = 0; i < 52; i++)//카드를 섞기 위해서 첫번째카드부터 j라는 난수를 발생시켜 그 칸의 카드와 위치를 바꾸는 방법
	{//첫 카드부터 52번째카드까지 위치를 조정해준다.
		if (i == 51)
			break;
		j = rand() % 52;
		temp = s->head;
		for (k = 0; k <= i; temp = temp->next, k++);
		tmp = temp->data;
		for (k = 0, temp = s->head; k < j; temp = temp->next, k++);
		tmp1 = temp->data;
		for (k = 0, temp = s->head; k <= i; temp = temp->next, k++);
		temp->data = tmp1;
		for (k = 0, temp = s->head; k < j; temp = temp->next, k++);
		temp->data = tmp;
	}
}
int divide_card(LIST *s, LIST *p_or_d)
{
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->next = NULL;//덱에 있던 카드를 플레이어나 딜러에게 주는 함수이다.
	temp = s->head;
	s->head = s->head->next;
	s->count--;

	if (p_or_d->head == NULL)
		p_or_d->head = temp;
	else
		p_or_d->tail->next = temp;
	p_or_d->tail = temp;
	p_or_d->count++;
}
int turn_player(LIST *deck, LIST *p, int sum_p)
{
	char cdd[20] = { NULL };
	if (sum_p < 21)
	{
		printf("Hit or Stay? ");
		scanf("%s", cdd);
		if ((cdd[0] == 'h' || cdd[0] == 'H') && (cdd[1] == 'i' || cdd[1] == 'I') && (cdd[2] == 't' || cdd[2] == 'T') && cdd[3] == NULL)
		{
			divide_card(deck, p);//입력 받을 때 hit대소문자 빼고는 예외처리를 해주었다.
			return 1;
		}
		else if ((cdd[0] == 's' || cdd[0] == 'S') && (cdd[1] == 't' || cdd[1] == 'T') && (cdd[2] == 'a' || cdd[2] == 'A') && (cdd[3] == 'y' || cdd[3] == 'Y') && cdd[4] == NULL)
		{
			return 2;//위와 마찬가지로 예외처리 해주었다.
		}
		else
		{
			printf("유효하지 않은 입력값입니다!\n");
			return 0;
		}
	}return 1;//return 값을 각각 다르게 해주었다.(딜러턴으로 진입하기 위해서)
}
int turn_dealer(LIST *deck, LIST *d, int sum_d)
{
	if (sum_d < 17)
	{
		printf("딜러가 Hit합니다....\n");//딜러가 hit할 경우
		divide_card(deck, d);
		return 1;
	}
	else if (sum_d >= 17)
	{
		printf("딜러가 Stay합니다.\n");
		return 2;//딜러의 stay하는 경우 return값을 다르게 해서 승패판정으로 간다.
	}
}
int wins(int sum_p, int sum_d, int pro, LIST *d)
{
	printf("-----------------------------------------\n");//승리시와 패배시, 블랙잭일 경우의 리턴값을 다르게 해서 현재 소지금을 main에서 조정할 수 있게했다.
	if (sum_p > 21)
	{
		printf("버스트! 플레이어가 졌습니다. 배팅한 돈을 잃었습니다.\n");
		return 3;
	}
	else if (sum_d == 21 && d->count == 2)
	{
		printf("딜러가 ★B★L★A★C★K★J★A★C★K★\n배팅한 돈을 잃었습니다.\n");
		return 0;
	}
	else if (sum_p > 0 && sum_p < 21 && sum_d>21)
	{
		printf("플레이어가 이겼습니다! $%d를 획득했습니다.\n", pro * 2);
		return 4;
	}
	else if (sum_d > 0 && sum_d < 21 && sum_p > 0 && sum_p&&sum_d > sum_p)
	{
		printf("딜러가 이겼습니다. 배팅한 돈을 잃었습니다.\n");
		return 3;
	}
	else if (sum_p > 0 && sum_p < 21 && sum_d > 0 && sum_d < 21)
	{
		if (sum_p >= sum_d)
		{
			printf("플레이어가 이겼습니다! $%d를 획득했습니다.\n", pro * 2);
			return 4;
		}
		else if (sum_p < sum_d)
		{
			printf("플레이어가 졌습니다. 배팅한 돈을 잃었습니다.\n");
			return 3;
		}
	}
}
