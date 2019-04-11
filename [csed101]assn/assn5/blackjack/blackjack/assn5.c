#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "assn5.h"//�⺻������ �ʿ��� ����� assn5.h�� include �Ѵ�
int main(int argc, char *argv[2])
{
	int money, o_money, pro, i, a, b, c, d, sum_p, sum_d, tp, td = 0, result, t, io,op,j=0,u=0,y=0;//������ ���� ������ �����ϰڴ�.
	LIST deck, player, dealer;//ī��¦���� LIST��� �ϰ� ���� deck�� �÷��̾� �׸��� ������ ī��¦������ �����Ѵ�.
	NODE *tmpp;//�Ҵ������� �ϱ� ���ؼ� tmpp�� �������ش�.
	srand(time(NULL));
	deck.count = 0;
	deck.head = NULL;
	deck.tail = NULL;
	player.count = 0;
	player.head = NULL;
	player.tail = NULL;
	dealer.count = 0;
	dealer.head = NULL;
	dealer.tail = NULL;//ó�� 3������ ī��¦���� �ʱ�ȭ��Ų��.
	if (argv[1] == NULL)//argv���� argv[0]���� assn5�� ���� ������ �� ���� ĭ��argv[1]�� ���� �Է¹ޱ�� �Ѵ�.
	{
		money = 5000;
	}
	else if (argv[1] != NULL)
	{
		money = atoi(argv[1]);
	}
	o_money = money;//money�� ������ ����� ������ �ٲ�� ����������̰� o_money�� ���� ó�� �Է¹��� ��(ó����)�̴�.
	while (1)
	{
		
		pro = bet(money, o_money);//pro�� ������ ��ŭ�� ���̴�.
		if (pro == 0)//0�� �Է����� ���� ������ ���ߵ��� �Ѵ�.
			break;
		else if (deck.count == 0)//������ ���� �Է� �Ǿ����� ���� ī�带 �����Ѵ�.
		{
			for (t = 0; t < 52; t++)
				insert_node(&deck, t);
			shuffle_card(&deck);//������ ī�带 �����ش�,
		}
		money = money - pro;//���� �����ݿ��� ������ ��ŭ�� ���� ���ش�.(�׷��� ���� �������� �ȴ�.)
		divide_card(&deck, &player);//�÷��̾� ���� ������ ī�带 ���� �����ش�.
		divide_card(&deck, &dealer);
		divide_card(&deck, &player);
		divide_card(&deck, &dealer);

		a = player.head->data.numb;
		b = player.head->next->data.numb;
		c = dealer.head->data.numb;
		d = dealer.head->next->data.numb;

		a = is_numb(a);//���⼭ ���� ī���� ������ ����ȭ �����ش�. �ڼ��� ������ function�κп� �ִ�.
		b = is_numb(b);
		c = is_numb(c);
		d = is_numb(d);
		sum_p = a + b;
		sum_d = c + d;
		
		if (a == 0)
			a = is_A(a, sum_p);
		if (b == 0)
			b = is_A(b, sum_p);
		if (c == 0)
			c = is_A(c, sum_d);
		if (d == 0)
			d = is_A(d, sum_d);
		if (a == 11 && b == 11)
			sum_p = 12;
		if (c == 11 && d == 11)
			sum_d = 12;
		sum_p = a + b;
		sum_d = c + d;
		
		tp = 4;//�ݺ����� ����� �۵��ǰ� �Ϸ��� ���Ƿ� ���� �������ش�.
		while (1)//������ ����Ǵ� �ݺ����̴�.
		{
			
			if (deck.count <= 26) //26�������� ��� �� �Ҵ����� �� �ٽ� ����
			{
				system("cls");
				printf("ī�带 ���Ӱ� �����ϴ�...\n");
				for (i = 0; i < deck.count; i++)
				{
					tmpp = deck.head;
					deck.head = deck.head->next;
					free(tmpp);
				}
				deck.count = 0;
				deck.head = NULL;
				deck.tail = NULL;//�ٽ� ���� �ʱ�ȭ��Ų��.
				for (t = 0; t < 52; t++)
					insert_node(&deck, t);//�� ���� ī�带 �ٽ� �����Ѵ�.
				shuffle_card(&deck);//���⼭ ī�带 �ٽ� ���´�.
				money = money + pro;//��� ���� ���� �ٽ� �ش�.(ī�带 ���� ��� ���������� �ȵǾ)
				break;
			}
			if (tp == 0)//tp�� ���� 0�̶�� ��ȿ���� ���� �Է��� ����̴�.(�÷��̾��� �Ͽ���)
			{
				tp = turn_player(&deck, &player, sum_p);
				print_game(&dealer, &player, sum_d, sum_p, money, pro, tp);
			}
			else if (tp == 1)//�÷��̾� �Ͽ��� hit�ϰ� �Ǹ� tp�� 1�� ����ȴ�.
			{
				a = player.tail->data.numb;//��� ���� ī�尪�� ���� ó���̴�.
				a = is_numb(a);
				sum_p = sum_p + a;
				if (a == 0)
				{
					a = is_A(a, sum_p);
					sum_p = sum_p + a;
				}
				
				if (player.head->data.numb == 65 || player.head->next->data.numb == 65&&u==0)//A���� ��ȭ��Ű�°�
				{
					c = player.head->data.numb;
					d = player.head->next->data.numb;
					c = is_numb(c);
					d = is_numb(d);

					if (c == 0)
					{
						c = is_A(c, sum_p);
						j++;
					}
					if (d == 0)
					{
						d = is_A(d, sum_p);
						j++;
					}
					sum_p = sum_p - 10 * j;
					u++;
				}j = 0;
				print_game(&dealer, &player, sum_d, sum_p, money, pro, tp);

				if (sum_p > 21)//�÷��̾ bust�Ǹ� �ٷ� tp�� 2�� �����ϰ� ���� ������ �Ѿ��.
					tp = 2;
				else//21���ϰ� �Ǹ� �÷��̾��� ���� �̾��.
					tp = turn_player(&deck, &player, sum_p);
			}
			else if (tp == 2)//������ ������ �Ѿ�� ���̴�.
			{
				print_game(&dealer, &player, sum_d, sum_p, money, pro, tp);
				td = turn_dealer(&deck, &dealer, sum_d);//������ ���� �����Ѵ�.
				if (td == 1)//������ �Ͽ��� hit������ �÷��̾��� �ϰ� ���� ���� ī�忡 ���� ó���Ѵ�.
				{
					c = dealer.tail->data.numb;
					c = is_numb(c);
					sum_d = sum_d + c;
					if (c == 0)
					{
						c = is_A(c, sum_d);
						sum_d = sum_d + c;
					}
				}
				while (sum_d < 17)//����ī���� ����17�̸��̸� ��� hit�ϱ� ���� �ݺ����̴�.
				{
					td = turn_dealer(&deck, &dealer, sum_d);
					c = dealer.tail->data.numb;
					c = is_numb(c);
					sum_d = sum_d + c;
					if (c == 0)
					{
						c = is_A(c, sum_d);
						sum_d = sum_d + c;
					}
					
					if (dealer.head->data.numb == 65 || dealer.head->next->data.numb == 65&&y==0)//A���� �ٽ� ��ȭ��Ű�°�
					{
						a = dealer.head->data.numb;
						b = dealer.head->next->data.numb;
						a = is_numb(a);
						b = is_numb(b);
						
						if (a == 0)
						{
							a = is_A(a, sum_d);
							j++;
						}
						if (b == 0)
						{
							b = is_A(b, sum_d);
							j++;
						}
						sum_d = sum_d - 10*j;
						y++;
					}
				}
				if (td == 2)//������ ������ ���� ��쿡 �ٷ� ��������(������ ��)�� �����Ѵ�.
				{
					result = wins(sum_p, sum_d, pro, &dealer);

					if (result == 4)//�÷��̾ �̰��� ��� result��4�� ������ ���� ȹ���Ѵ�. �ƴ� ��� ���� �ҰԵȴ�.
					{
						money = money + 2 * pro;
					}
					//�Ҵ����� 
					for (io = 0; io < player.count; io++)
					{
						tmpp = player.head;
						if (io != player.count - 1)
							player.head = player.head->next;
						else if (io == player.count - 1)
							tmpp = player.tail;
						free(tmpp);
					}
					for (io = 0; io < dealer.count; io++)
					{
						tmpp = dealer.head;
						if (io != dealer.count - 1)
							dealer.head = dealer.head->next;
						else if (io == dealer.count - 1)
							tmpp = dealer.tail;
						free(tmpp);
					}
					dealer.head = NULL;//������ ���� �ڿ� ��� ���� ī����� ������.
					player.head = NULL;
					dealer.tail = NULL;
					player.tail = NULL;
					dealer.count = 0;
					player.count = 0;
					break;
				}
			}
			else
			{
				print_game(&dealer, &player, sum_d, sum_p, money, pro, tp);//�� �κ��� ó���� �ݺ��� �ۿ���tp�� ������ ���� �����ؼ� ��ó�� �÷��̾��� ���� �����ϰ� ���ִºκ��̴�.
				tp = turn_player(&deck, &player, sum_p);
			}
			if (sum_p == 21 && player.count == 2)//���� ��������� �ް� ī������ 21�� �ȴٸ� �������� ������ ������.
			{
				printf("��B��L��A��C��K��J��A��C��K��");
				printf("������ �ݾ��� 3�迡 �ش��ϴ� $%d�� ȹ���߽��ϴ�.\n", pro * 3);
				money = money + pro * 3;
				break;
			}
		}
		//�Ҵ�����
		for (io = 0; io < player.count; io++)
		{
			tmpp = player.head;
			if (io != player.count - 1)
				player.head = player.head->next;
			else if (io == player.count - 1)
				tmpp = player.tail;
			free(tmpp);
		}
		for (io = 0; io < dealer.count; io++)
		{
			tmpp = dealer.head;
			if (io != dealer.count - 1)
				player.head = dealer.head->next;
			else if (io == dealer.count - 1)
				tmpp = dealer.tail;
			free(tmpp);
		}
		dealer.head = NULL;//������ ���� �ڿ� ��� ���� ī����� ������.
		player.head = NULL;
		dealer.tail = NULL;
		player.tail = NULL;
		dealer.count = 0;
		player.count = 0;
	}
	return 0;
}
