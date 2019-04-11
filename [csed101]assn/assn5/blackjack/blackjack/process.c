#include "assn5.h"
#include <stdio.h>//NULL���� ����� ���� ��Ŭ�����.
int bet(int money, int o_money)//���ð����� �����ϴ� �Լ��̴�.
{
	int betmoney;
	if (money > o_money * 100)//����ó���̴�
	{
		printf("����� ���� �ʹ� ���� ���� ī���� ��ü�� ����� �ѾƳ½��ϴ�!\n");
		printf("ī���뿡�� $%d�� ���� $%d�� �������ϴ�!!!\n", o_money, money);
		return 0;
	}
	if (money == 0)//����ó��
	{
		printf("����� ��� ī���뿡�� �Ѱܳ����ϴ�...\n");
		printf("���� ������ �ϸ� �ȵſ�...\n");
		return 0;
	}

	while (1)//��ȿ�� �ݾ��� �Է��� ������ �Է¹ް� ��.
	{
		printf("[���� ������: $%d] ���� �ݾ��� �����ϼ���! <0 for Exit>", money);
		scanf("%d", &betmoney);

		if (betmoney<0 || betmoney>money)
		{
			printf("��ȿ�� ���ñݾ��� �������ּ���!\n");
		}
		else
			break;
	}

	if (betmoney == 0)//���α׷� ����ÿ� ������ִ� �Լ��̴�.
	{
		printf("����� $%d�� ����� $%d�� ���ܿԽ��ϴ�.\n", o_money, money);
		return 0;
	}

	return betmoney;
}
void insert_node(LIST *plist, int t)
{
	NODE *NEW;//NODE�� �����ؼ� �����ϱ� ���� NEW��� ��� �Ҵ� �� ���� plist�� �������ش�.

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
	if (t >= 0 && t < 13)//ī�带 ������� �޾��ش�.
	{
		s->shape = "��";
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
		s->shape = "��";
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
		s->shape = "��";
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
		s->shape = "��";
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

	for (i = 0; i < 52; i++)//ī�带 ���� ���ؼ� ù��°ī����� j��� ������ �߻����� �� ĭ�� ī��� ��ġ�� �ٲٴ� ���
	{//ù ī����� 52��°ī����� ��ġ�� �������ش�.
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
	temp->next = NULL;//���� �ִ� ī�带 �÷��̾ �������� �ִ� �Լ��̴�.
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
			divide_card(deck, p);//�Է� ���� �� hit��ҹ��� ����� ����ó���� ���־���.
			return 1;
		}
		else if ((cdd[0] == 's' || cdd[0] == 'S') && (cdd[1] == 't' || cdd[1] == 'T') && (cdd[2] == 'a' || cdd[2] == 'A') && (cdd[3] == 'y' || cdd[3] == 'Y') && cdd[4] == NULL)
		{
			return 2;//���� ���������� ����ó�� ���־���.
		}
		else
		{
			printf("��ȿ���� ���� �Է°��Դϴ�!\n");
			return 0;
		}
	}return 1;//return ���� ���� �ٸ��� ���־���.(���������� �����ϱ� ���ؼ�)
}
int turn_dealer(LIST *deck, LIST *d, int sum_d)
{
	if (sum_d < 17)
	{
		printf("������ Hit�մϴ�....\n");//������ hit�� ���
		divide_card(deck, d);
		return 1;
	}
	else if (sum_d >= 17)
	{
		printf("������ Stay�մϴ�.\n");
		return 2;//������ stay�ϴ� ��� return���� �ٸ��� �ؼ� ������������ ����.
	}
}
int wins(int sum_p, int sum_d, int pro, LIST *d)
{
	printf("-----------------------------------------\n");//�¸��ÿ� �й��, ������ ����� ���ϰ��� �ٸ��� �ؼ� ���� �������� main���� ������ �� �ְ��ߴ�.
	if (sum_p > 21)
	{
		printf("����Ʈ! �÷��̾ �����ϴ�. ������ ���� �Ҿ����ϴ�.\n");
		return 3;
	}
	else if (sum_d == 21 && d->count == 2)
	{
		printf("������ ��B��L��A��C��K��J��A��C��K��\n������ ���� �Ҿ����ϴ�.\n");
		return 0;
	}
	else if (sum_p > 0 && sum_p < 21 && sum_d>21)
	{
		printf("�÷��̾ �̰���ϴ�! $%d�� ȹ���߽��ϴ�.\n", pro * 2);
		return 4;
	}
	else if (sum_d > 0 && sum_d < 21 && sum_p > 0 && sum_p&&sum_d > sum_p)
	{
		printf("������ �̰���ϴ�. ������ ���� �Ҿ����ϴ�.\n");
		return 3;
	}
	else if (sum_p > 0 && sum_p < 21 && sum_d > 0 && sum_d < 21)
	{
		if (sum_p >= sum_d)
		{
			printf("�÷��̾ �̰���ϴ�! $%d�� ȹ���߽��ϴ�.\n", pro * 2);
			return 4;
		}
		else if (sum_p < sum_d)
		{
			printf("�÷��̾ �����ϴ�. ������ ���� �Ҿ����ϴ�.\n");
			return 3;
		}
	}
}
