#ifndef ASSN5_H
#define ASSN5_H
typedef struct
{
	char *shape;
	char numb;
}CARD;//ī�������� ���� ����ü
typedef struct node
{
	CARD data;
	struct node *next;
}NODE;//��� ������ �����ϴ� ����ü
typedef struct
{
	int count;
	NODE *head;
	NODE *tail;
}LIST;//���� ����Ʈ�� ������ �����ϴ� ����ü
void insert_node(LIST *plist, int t);//ī�带 ������ �� ��带 ���� �Ҵ��ϴ� �Լ��̴�.
void add_card(CARD *s, int t);//�Ҵ�� ��忡 ī�带 ����ִ� �Լ��̴�.
void shuffle_card(LIST *s);//ī�嵦�� �ϼ��� �� ī�带 ���� �Լ��̴�.
int bet(int t, int k);//���ð����� �����ϴ� �Լ��̴�.
int divide_card(LIST *s, LIST *p_or_d);//ī�带 �������ִ� �Լ��̴�.
void print_game(LIST *d, LIST *p, int sum_d, int sum_p, int money, int pro, int tp);//���� ����� ����ϴ� �Լ�
int turn_player(LIST *deck, LIST *p, int sum_p);//�÷��̾��� �����Լ�
int turn_dealer(LIST *deck, LIST *d, int sum_d);//������ �����Լ�
int wins(int sum_p, int sum_d, int pro); //���������Լ�
int is_numb(int a);//�������� KQJA���� �������� �Ǵ�
int is_A(int a, int sum);//A�ϰ�� A���� � ������ ���� �Ǵ����ִ� �Լ�
#endif
