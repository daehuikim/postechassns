#include<stdio.h>
#include"map.h"
#include <stdlib.h>
#include <time.h>	//���࿡ �ʿ��� ����� �����ϰ� ������ ���map.h�� �����Ѵ�.
void CreateMap(char main_map[][MAP_COL]);		//�ʻ����ϴ� �Լ��̴�.
void DrawCircle(int center_row, int center_col, int radius, char main_map[][MAP_COL]);//�ʿ� ���� �׸��� �Լ��̴�.
void DrawSquare(int top_left_row, int top_left_col, int bottom_right_row, int bottom_right_col, char main_map[][MAP_COL]);//�ʿ� �簢���� �����ϴ� �Լ��̴�.
void PrintMap(char main_map[][MAP_COL], int current_row, int current_col);//������� ȭ���� ����ϴ� �Լ��̴�.
int main()
{
	char main_map[MAP_ROW][MAP_COL], view_map[VIEW_ROW][VIEW_COL], put;//��ü��,������� ȭ���� �������迭�� ����
	int current_row, current_col, range;//������� ȭ����ǥ�� �޴� �� ����

	srand(time(NULL));
	range = (MAP_ROW - 0);		//�ʱ� ������� ȭ���� ������ �����Ѵ�. �� ��, ȭ�� ���� ����� �ʵ��� �ߴ�.
	current_row = rand() % range + 0;
	range = (MAP_COL - 0);
	current_col = rand() % range + 0;

	CreateMap(main_map);//�ʻ��� �Լ��� ȣ���Ѵ�.
	PrintMap(main_map, current_row, current_col);//������� ȭ���� ����Ѵ�.

	while (1)
	{
		scanf("%c", &put);//��ɾ ���� ������� ȭ�� �̵��̴�.
		if (put == 'h')
			current_col = current_col - 1;
		else if (put == 'H')
			current_col = current_col - MOVE_STEP;
		else if (put == 'l')
			current_col = current_col + 1;
		else if (put == 'L')
			current_col = current_col + MOVE_STEP;
		else if (put == 'j')
			current_row = current_row + 1;
		else if (put == 'J')
			current_row = current_row + MOVE_STEP;
		else if (put == 'k')
			current_row = current_row - 1;
		else if (put == 'K')
			current_row = current_row - MOVE_STEP;
		else if (put == 'c')
			current_row = MAP_ROW / 2, current_col = MAP_COL / 2;
		else if (put == 'q')
			return 0;

		if (current_row < 0) //������� ȭ���� �� �ٱ����� ������ ���� ���� ���� ó���̴�.
			current_row = 0;
		if (current_row > MAP_ROW - 1)
			current_row = MAP_ROW - 1;
		if (current_col < 0)
			current_col = 0;
		if (current_col > MAP_COL - 1)
			current_col = MAP_COL - 1;

		system("clear");
		PrintMap(main_map, current_row, current_col);
	}//�� �ݺ����� ���ؼ� �Է¹��� ���� ���� ���̵��� ��� �����ϴ�.

	return 0;
}
void CreateMap(char main_map[][MAP_COL])
{
	int i, j;//�� ���� �� ó������ ' '�� ��� ������ ä���.
	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			main_map[i][j] = ' ';

	DrawCircle(MAP_ROW / 2, MAP_COL / 2, RADIUS, main_map);//�ش��Լ� ȣ���� ���� �� �߰��� ���� �׸���.
	DrawSquare(10, 10, 20, 40, main_map);//�ش��Լ� ȣ���� ���ؼ� �簢���� �׸���.
	DrawSquare(25, 15, 30, 30, main_map);//�ش��Լ� ȣ���� ���ؼ� �簢���� �׸���.
}
void DrawCircle(int center_row, int center_col, int radius, char main_map[][MAP_COL])
{
	int x, y;
	for (y = 0; y < MAP_ROW; y++)//�� ��ü�� �˻��ϸ鼭, �Ѱܹ��� ������ ����Ͽ� �� ������ �ȿ� ���Ե� �κ��� 'c'�� ä���.
		for (x = 0; x < MAP_COL; x++)
			if ((x - center_col)*(x - center_col) + (y - center_row)*(y - center_row) <= radius*radius)
			{
				main_map[y][x] = 'c';
			}
}
void DrawSquare(int top_left_row, int top_left_col, int bottom_right_row, int bottom_right_col,
	char main_map[][MAP_COL])
{
	int x, y;
	for (y = 0; y < MAP_ROW; y++)//����ü�� �˻��ϸ鼭, �Ѱܹ��� ������ ����Ͽ� ���ǹ��� �´� �κ�(�� ���� �������� �� ���簢��)�� 's'�� ä���.
		for (x = 0; x < MAP_COL; x++)
		{
			if ((bottom_right_row >= y && y >= top_left_row) && (bottom_right_col >= x && x >= top_left_col))
			{
				main_map[y][x] = 's';
			}
		}
}
void PrintMap(char main_map[][MAP_COL], int current_row, int current_col)
{
	int x, y;//������� ȭ���� ����ϴ� �Լ��̴�.
	printf("-------------------------------------\n");
	for (y = current_row - VIEW_ROW / 2; y < current_row + VIEW_ROW / 2; y++)//currnt_row,col�� �߽����� ���� ��ƴ ��ŭ���� ����ϰ��Ѵ�.
	{
		printf("|");
		for (x = current_col - VIEW_COL / 2; x < current_col + VIEW_COL / 2; x++)
		{
			if ((x >= 0 && x<MAP_COL) && (y >= 0 && y<MAP_ROW))//���� ȭ���� �ʾ��� ����� ��Ÿ���ٸ� �״�� ��Ÿ����
			{
				printf("%c", main_map[y][x]);
			}
			else                                //�� ���� ����� ���´ٸ� 'x'�� ǥ���Ѵ�.
			{
				main_map[y][x] = 'x';
				printf("%c", main_map[y][x]);
			}
		}
		printf("|\n");//�ش� ó���� �簢�� �ȿ� ȭ���� ��Ÿ���� �����̴�.
	}
	printf("----------ROW: %2d, COL: %2d-----------\n", current_row, current_col);//������� ���� ȭ���� ������ �迭������ ��ǥ�� ��Ÿ���ش�.
}
