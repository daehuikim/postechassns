#include<stdio.h>
#include"map.h"
#include <stdlib.h>
#include <time.h>	//실행에 필요한 헤더를 포함하고 생성한 헤더map.h도 포함한다.
void CreateMap(char main_map[][MAP_COL]);		//맵생성하는 함수이다.
void DrawCircle(int center_row, int center_col, int radius, char main_map[][MAP_COL]);//맵에 원을 그리는 함수이다.
void DrawSquare(int top_left_row, int top_left_col, int bottom_right_row, int bottom_right_col, char main_map[][MAP_COL]);//맵에 사각형을 생성하는 함수이다.
void PrintMap(char main_map[][MAP_COL], int current_row, int current_col);//사용자의 화면을 출력하는 함수이다.
int main()
{
	char main_map[MAP_ROW][MAP_COL], view_map[VIEW_ROW][VIEW_COL], put;//전체맵,사용자의 화면을 이차원배열로 생성
	int current_row, current_col, range;//사용자의 화면좌표를 받는 값 생성

	srand(time(NULL));
	range = (MAP_ROW - 0);		//초기 사용자의 화면을 난수로 생성한다. 이 때, 화면 밖을 벗어나지 않도록 했다.
	current_row = rand() % range + 0;
	range = (MAP_COL - 0);
	current_col = rand() % range + 0;

	CreateMap(main_map);//맵생성 함수를 호출한다.
	PrintMap(main_map, current_row, current_col);//사용자의 화면을 출력한다.

	while (1)
	{
		scanf("%c", &put);//명령어에 따른 사용자의 화면 이동이다.
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

		if (current_row < 0) //사용자의 화면이 맵 바깥으로 나가는 것을 막기 위한 처리이다.
			current_row = 0;
		if (current_row > MAP_ROW - 1)
			current_row = MAP_ROW - 1;
		if (current_col < 0)
			current_col = 0;
		if (current_col > MAP_COL - 1)
			current_col = MAP_COL - 1;

		system("clear");
		PrintMap(main_map, current_row, current_col);
	}//위 반복문을 통해서 입력받은 값을 통한 맵이동이 계속 가능하다.

	return 0;
}
void CreateMap(char main_map[][MAP_COL])
{
	int i, j;//맵 생성 시 처음에는 ' '로 모든 공간을 채운다.
	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			main_map[i][j] = ' ';

	DrawCircle(MAP_ROW / 2, MAP_COL / 2, RADIUS, main_map);//해당함수 호출을 통해 맵 중간에 원을 그린다.
	DrawSquare(10, 10, 20, 40, main_map);//해당함수 호출을 통해서 사각형을 그린다.
	DrawSquare(25, 15, 30, 30, main_map);//해당함수 호출을 통해서 사각형을 그린다.
}
void DrawCircle(int center_row, int center_col, int radius, char main_map[][MAP_COL])
{
	int x, y;
	for (y = 0; y < MAP_ROW; y++)//맵 전체를 검사하면서, 넘겨받은 값들을 계산하여 원 방정식 안에 포함된 부분을 'c'로 채운다.
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
	for (y = 0; y < MAP_ROW; y++)//맵전체를 검사하면서, 넘겨받은 값들을 계산하여 조건문에 맞는 부분(두 점을 기준으로 한 직사각형)을 's'로 채운다.
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
	int x, y;//사용자의 화면을 출력하는 함수이다.
	printf("-------------------------------------\n");
	for (y = current_row - VIEW_ROW / 2; y < current_row + VIEW_ROW / 2; y++)//currnt_row,col을 중심으로 양쪽 반틈 만큼씩을 출력하게한다.
	{
		printf("|");
		for (x = current_col - VIEW_COL / 2; x < current_col + VIEW_COL / 2; x++)
		{
			if ((x >= 0 && x<MAP_COL) && (y >= 0 && y<MAP_ROW))//만약 화면이 맵안의 모습을 나타낸다면 그대로 나타내고
			{
				printf("%c", main_map[y][x]);
			}
			else                                //맵 밖의 모습이 나온다면 'x'로 표시한다.
			{
				main_map[y][x] = 'x';
				printf("%c", main_map[y][x]);
			}
		}
		printf("|\n");//해당 처리는 사각형 안에 화면을 나타내기 위함이다.
	}
	printf("----------ROW: %2d, COL: %2d-----------\n", current_row, current_col);//사용자의 현재 화면의 이차원 배열에서의 좌표를 나타내준다.
}
