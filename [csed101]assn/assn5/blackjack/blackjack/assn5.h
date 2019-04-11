#ifndef ASSN5_H
#define ASSN5_H
typedef struct
{
	char *shape;
	char numb;
}CARD;//카드정보에 관한 구조체
typedef struct node
{
	CARD data;
	struct node *next;
}NODE;//노드 정보를 포함하는 구조체
typedef struct
{
	int count;
	NODE *head;
	NODE *tail;
}LIST;//연결 리스트의 정보를 포함하는 구조체
void insert_node(LIST *plist, int t);//카드를 생성할 때 노드를 먼저 할당하는 함수이다.
void add_card(CARD *s, int t);//할당된 노드에 카드를 집어넣는 함수이다.
void shuffle_card(LIST *s);//카드덱이 완성된 후 카드를 섞는 함수이다.
int bet(int t, int k);//베팅과정을 포함하는 함수이다.
int divide_card(LIST *s, LIST *p_or_d);//카드를 나누어주는 함수이다.
void print_game(LIST *d, LIST *p, int sum_d, int sum_p, int money, int pro, int tp);//게임 장면을 출력하는 함수
int turn_player(LIST *deck, LIST *p, int sum_p);//플레이어턴 진행함수
int turn_dealer(LIST *deck, LIST *d, int sum_d);//딜러턴 진행함수
int wins(int sum_p, int sum_d, int pro); //승패판정함수
int is_numb(int a);//숫자인지 KQJA같은 문자인지 판단
int is_A(int a, int sum);//A일경우 A값을 어떤 값으로 볼지 판단해주는 함수
#endif
