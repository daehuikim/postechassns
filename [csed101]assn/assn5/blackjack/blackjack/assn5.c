#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "assn5.h"//기본적으로 필요한 헤더와 assn5.h를 include 한다
int main(int argc, char *argv[2])
{
	int money, o_money, pro, i, a, b, c, d, sum_p, sum_d, tp, td = 0, result, t, io,op,j=0,u=0,y=0;//변수는 나올 때마다 설명하겠다.
	LIST deck, player, dealer;//카드짝들을 LIST라고 하고 각각 deck과 플레이어 그리고 딜러의 카드짝정보를 갖게한다.
	NODE *tmpp;//할당해제를 하기 위해서 tmpp를 생성해준다.
	srand(time(NULL));
	deck.count = 0;
	deck.head = NULL;
	deck.tail = NULL;
	player.count = 0;
	player.head = NULL;
	player.tail = NULL;
	dealer.count = 0;
	dealer.head = NULL;
	dealer.tail = NULL;//처음 3종류의 카드짝들을 초기화시킨다.
	if (argv[1] == NULL)//argv에서 argv[0]에는 assn5가 들어가기 때문에 그 다음 칸인argv[1]에 대해 입력받기로 한다.
	{
		money = 5000;
	}
	else if (argv[1] != NULL)
	{
		money = atoi(argv[1]);
	}
	o_money = money;//money는 게임이 진행될 때마다 바뀌는 현재소지금이고 o_money는 제일 처음 입력받은 값(처음돈)이다.
	while (1)
	{
		
		pro = bet(money, o_money);//pro는 베팅한 만큼의 돈이다.
		if (pro == 0)//0을 입력했을 때는 게임을 멈추도록 한다.
			break;
		else if (deck.count == 0)//적절한 돈이 입력 되었으면 이제 카드를 생성한다.
		{
			for (t = 0; t < 52; t++)
				insert_node(&deck, t);
			shuffle_card(&deck);//생성한 카드를 섞어준다,
		}
		money = money - pro;//현재 소지금에서 베팅한 만큼의 돈을 빼준다.(그래야 현재 소지금이 된다.)
		divide_card(&deck, &player);//플레이어 딜러 순으로 카드를 두장 나눠준다.
		divide_card(&deck, &dealer);
		divide_card(&deck, &player);
		divide_card(&deck, &dealer);

		a = player.head->data.numb;
		b = player.head->next->data.numb;
		c = dealer.head->data.numb;
		d = dealer.head->next->data.numb;

		a = is_numb(a);//여기서 받은 카드의 값들을 숫자화 시켜준다. 자세한 설명은 function부분에 있다.
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
		
		tp = 4;//반복문이 제대로 작동되게 하려고 임의로 값을 지정해준다.
		while (1)//게임이 진행되는 반복문이다.
		{
			
			if (deck.count <= 26) //26장이하일 경우 다 할당해제 후 다시 생성
			{
				system("cls");
				printf("카드를 새롭게 섞습니다...\n");
				for (i = 0; i < deck.count; i++)
				{
					tmpp = deck.head;
					deck.head = deck.head->next;
					free(tmpp);
				}
				deck.count = 0;
				deck.head = NULL;
				deck.tail = NULL;//다시 덱을 초기화시킨다.
				for (t = 0; t < 52; t++)
					insert_node(&deck, t);//그 이후 카드를 다시 생성한다.
				shuffle_card(&deck);//여기서 카드를 다시 섞는다.
				money = money + pro;//방금 받은 돈을 다시 준다.(카드를 새로 섞어서 게임진행이 안되어서)
				break;
			}
			if (tp == 0)//tp의 값이 0이라면 유효하지 않은 입력일 경우이다.(플레이어의 턴에서)
			{
				tp = turn_player(&deck, &player, sum_p);
				print_game(&dealer, &player, sum_d, sum_p, money, pro, tp);
			}
			else if (tp == 1)//플레이어 턴에서 hit하게 되면 tp에 1이 저장된다.
			{
				a = player.tail->data.numb;//방금 받은 카드값에 대한 처리이다.
				a = is_numb(a);
				sum_p = sum_p + a;
				if (a == 0)
				{
					a = is_A(a, sum_p);
					sum_p = sum_p + a;
				}
				
				if (player.head->data.numb == 65 || player.head->next->data.numb == 65&&u==0)//A값을 변화시키는것
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

				if (sum_p > 21)//플레이어가 bust되면 바로 tp에 2를 저장하고 딜러 턴으로 넘어간다.
					tp = 2;
				else//21이하가 되면 플레이어의 턴을 이어간다.
					tp = turn_player(&deck, &player, sum_p);
			}
			else if (tp == 2)//딜러의 턴으로 넘어갔을 때이다.
			{
				print_game(&dealer, &player, sum_d, sum_p, money, pro, tp);
				td = turn_dealer(&deck, &dealer, sum_d);//딜러의 턴을 진행한다.
				if (td == 1)//딜러의 턴에서 hit했을때 플레이어의 턴과 같이 받은 카드에 대해 처리한다.
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
				while (sum_d < 17)//딜러카드의 합이17미만이면 계속 hit하기 위한 반복문이다.
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
					
					if (dealer.head->data.numb == 65 || dealer.head->next->data.numb == 65&&y==0)//A값을 다시 변화시키는것
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
				if (td == 2)//딜러가 스테이 했을 경우에 바로 승패판정(게임의 끝)을 시작한다.
				{
					result = wins(sum_p, sum_d, pro, &dealer);

					if (result == 4)//플레이어가 이겼을 경우 result에4가 들어오고 돈을 획득한다. 아닌 경우 돈만 잃게된다.
					{
						money = money + 2 * pro;
					}
					//할당해제 
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
					dealer.head = NULL;//게임이 끝난 뒤에 방금 썻던 카드들을 버린다.
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
				print_game(&dealer, &player, sum_d, sum_p, money, pro, tp);//이 부분은 처음에 반복문 밖에서tp에 임의의 값을 저장해서 맨처음 플레이어의 턴을 수행하게 해주는부분이다.
				tp = turn_player(&deck, &player, sum_p);
			}
			if (sum_p == 21 && player.count == 2)//만약 두장까지만 받고 카드합이 21이 된다면 블랙잭으로 게임이 끝난다.
			{
				printf("★B★L★A★C★K★J★A★C★K★");
				printf("배팅한 금액의 3배에 해당하는 $%d를 획득했습니다.\n", pro * 3);
				money = money + pro * 3;
				break;
			}
		}
		//할당해제
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
		dealer.head = NULL;//게임이 끝난 뒤에 방금 썻던 카드들을 버린다.
		player.head = NULL;
		dealer.tail = NULL;
		player.tail = NULL;
		dealer.count = 0;
		player.count = 0;
	}
	return 0;
}
