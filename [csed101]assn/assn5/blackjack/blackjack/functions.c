#include "assn5.h"//����� ��Ŭ����Ѵ�.
void print_game(LIST *d, LIST *p, int sum_d, int sum_p, int money, int pro, int tp)
{
	int i, j, k, l;
	NODE *temp;
	system("cls");//�׻� cls�� ���� print�� ������ �����ش�.
	printf("[������ : %d] [���ñݾ�: %d]\n", money, pro);
	printf("-----------------------------------------\n");
	printf("<Dealer> ");

	if (tp != 2)//�÷��̾� ���� ������ ùī�带 �������� �ʴ´�.
		printf("[????] ");

	else if (tp == 2)
	{
		temp = d->head;
		if (temp->data.numb > 58)//numb�� char���̱� ������ �ƽ�Ű �ڵ尪�� ���� ���� ū �빮���� ��� %c�� ���, ������ ��쿡�� %d�� ������ش�(�Ʒ��� �� �̷�����)
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
	k = d->head->data.numb;//���� ī�忡 ���� ���� �Ǻ�ó���̰� ���� �ٲ��ش�.
	k = is_numb(k);
	k = is_A(k, sum_d);
	if (tp != 2)
	{
		if (k == 1)
			k = 11;
		printf(", Sum=%d\n", sum_d - k);//ù��° �� ������ ���ֱ� ���� k���� ���ְ� ������ش�.
	}
	if (tp == 2)
		printf(", Sum=%d\n", sum_d);//���� �������� ���� ù��°ī����� ���ؼ� ���� ������ش�.
	printf("<Player> ");//�÷��̾��� ī��� ���Ͱ��� ��Ŀ�������� ���
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
	if (a == 74 || a == 75 || a == 81)//A�� �ƴ� JKQ�϶� 10���� �������ְ�
		a = 10;
	else if (a == 65)//A�϶��� �켱 0�� return�Ѵ�.
		a = 0;
	else
		return a;
	return a;
}
int is_A(int a, int sum)
{
	if (a == 0)//���� A�ϰ�� 0�� ���ϵǾ��� ������ ���⼭ ���� ũ�⸦ ���� �Ǻ����ش�.
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
