#include <stdio.h>
#include <stdlib.h>//위 두개는 필수 라이브러리
#include <string.h>//문자열 관련함수 사용 헤더
#include <Windows.h>//출력에 필요한 헤더

#define MAX_LOAD_IMG_SIZE 10//구조체 포인터 배열의 개수 제한
typedef struct
{
	int width; // 이미지의 넓이
	int height; // 이미지의 높이
	int compFlag; // 압축을 하였는가 0: No, 1: Yes
	char *imgName; // 이미지의 이름
	int **imgValue; // 이미지의 픽셀 값들
} IMGMAT;//구조체의 이름(이미지 정보)

void printIndex(IMGMAT **pic, int t);//메뉴1번
int loadImage(IMGMAT **pic, int t);  //메뉴2번
int printImage(IMGMAT **pic, int t); //메뉴3번
int RemoveImgae(IMGMAT**pic, int t); //메뉴4번
int zip(IMGMAT**pic, int t);        //메뉴5번
int mini(IMGMAT**pic, int t);       //메뉴6번
void EndPro(IMGMAT**pic, int t);	 //메뉴0번

int main()
{
	IMGMAT *pic[MAX_LOAD_IMG_SIZE];
	int t = 0, m, n, con = 1, i, o = 0,b;
	char check[256] = { NULL };
	system("mode con:cols=170 lines=95");

	while (1)
	{//매번 메뉴판을 출력한다.
		printf("====================================\n");
		printf("[1] 이미지 목록 보기\n");
		printf("[2] 이미지 로드\n");
		printf("[3] 이미지 출력\n");
		printf("[4] 이미지 제거\n");
		printf("[5] 이미지 압축\n");
		printf("[6] 이미지 축소\n");
		printf("[0] 종료\n");
		printf("====================================\n");
		printf("메뉴 번호 입력:");
		scanf("%s", check);

		if (check[0] == '1'&&check[1]==NULL)//1이외의 출력값은 이것을 받지 못하고 그 이후에도 같게했다.
		{
			printIndex(pic, t);
		}
		else if (check[0] == '2'&&check[1] == NULL)
		{
			m = loadImage(pic, t);
			if (m == 1)
				t++;
		}
		else if (check[0] == '3'&&check[1] == NULL)
		{
			b=printImage(pic, t);
		}
		else if (check[0] == '4'&&check[1] == NULL)
		{
			n = RemoveImgae(pic, t);
			if (n == 4);
			t--;//t는 이미지 받은 갯수이고 삭제시 - 로드시+한다.
		}
		else if (check[0] == '5'&&check[1] == NULL)
		{
			zip(pic, t);
		}
		else if (check[0] == '6'&&check[1] == NULL)
		{
			mini(pic, t);
		}
		else if (check[0] == '0'&&check[1] == NULL)
		{
			EndPro(pic, t);
			printf("프로그램이 종료되었습니다.\n");
			return 0;
		}
		else //0123456 이 아닌 이상에는 잘못된 값임을 알려준다.
		{
			printf("입력범위 안의 값이 아닙니다.\n");
		}
	}
}//main함수에서는 메뉴 출력과 프로그램 진행을 한다.
void printIndex(IMGMAT **pic, int t)
{//구조체 배열과 그 갯수를 받아서 이미지 목록의 이름을 출력한다.
	int i;
	if (t == 0)//아무 이미지도 없을 경우의 예외처리이다.
	{
		printf("로드한 이미지가 없습니다.\n");
	}
	else//이미지가 있을 경우에는 t(로드된 이미지 갯수)만큼 받은 순서대로 출력해준다.
	{
		for (i = 1; i <= t; i++)
			printf("[%d]번 이미지 이름: %s\n", i, pic[i - 1]->imgName);
	}
}
int loadImage(IMGMAT **pic, int t)
{
	int x, y, a, b, c, d, h = 0, l, k;
	int n, m;

	if (t >= 10)
	{
		printf("로드할 수 있는 범위를 넘었습니다.\n");
		return 2;
	}
	pic[t] = (IMGMAT*)malloc(sizeof(IMGMAT));//먼저 구조체 배열의 전체의 메모리를 동적할당한다.
	pic[t]->imgName = (char*)malloc(sizeof(char) * 30);//그리고 이미지 네임만큼의 메모리를 동적할당한다.
	printf("읽을 이미지 이름:");
	scanf("%s", pic[t]->imgName);

	pic[t]->imgName = (char*)realloc(pic[t]->imgName, sizeof(char)*(strlen(pic[t]->imgName) + 1));//그 후 받은 이름만큼 realloc한다.
	FILE *infile;
	infile = fopen(pic[t]->imgName, "r");//txt파일을 읽어들여서 메모리에 저장한다.
	if (infile == NULL)
	{
		printf("파일이 없습니다.\n");
		return 2;
	}
	else
	{
		fscanf(infile, "%d %d %d \n", &(pic[t]->height), &(pic[t]->width), &(pic[t]->compFlag));

		if (pic[t]->compFlag == 0)//압축되지 않은 파일의 로드형식으로, 이차원 배열을 동적할당하고 그 할당한 칸에 정보를 집어넣는다.
		{
			pic[t]->imgValue = (int**)malloc(sizeof(int*)*pic[t]->height);

			for (y = 0; y < pic[t]->height; y++)
			{
				pic[t]->imgValue[y] = (int*)malloc(sizeof(int)*pic[t]->width);
				for (x = 0; x < pic[t]->width; x++)
					fscanf(infile, "%d ", &(pic[t]->imgValue[y][x]));
			}
			printf("[%s]를 성공적으로 로드하였습니다.\n", pic[t]->imgName);
			return 1;
		}

		else if (pic[t]->compFlag == 1)//압축된 파일의 경우 2글자씩 읽으면서 10을 곱해준 값들을 imgValue에 집어넣어서 양자화시 같게 만들어주며 로드한다.
		{
			pic[t]->imgValue = (int**)malloc(sizeof(int*)*pic[t]->height);
			for (y = 0; y < pic[t]->height; y++)
				pic[t]->imgValue[y] = (int*)malloc(sizeof(int)*pic[t]->width);
			//value의 공간을 할당한다.
			m = 0;
			for (y = 0; y < pic[t]->height; y++)//파일 끝까지 읽으면서
				for (x = 0; x < pic[t]->width; x++)
				{
					if (m == 0)
						fscanf(infile, "%d %d ", &n, &m);
					pic[t]->imgValue[y][x] = n * 10;
					m--;
				}
		}
		printf("[%s]를 성공적으로 로드하였습니다.\n", pic[t]->imgName);
		return 1;
	}
}
int printImage(IMGMAT **pic, int t)
{
	int x, y, z, w, a, b, c, d, e;
	char num[256] = { NULL };
	printf("출력할 이미지 번호:ex<2or2-4>");
	scanf("%s", num);
	//1-10까지만 입력할 수 있기 때문에 5칸짜리 문자열을 선언한 후 -가 입력된 경우와 아닌경우에 대해 나눠서 생각한다.
	b = num[0] - '0';
	c = num[1] - '0';
	
	if (b < 1 || (c >= 1 && b >= 0))
	{
		printf("잘못된 입력범위 입니다.\n");
		return 7;//숫자범위를 벗어난 예외처리이다.
	}

	if (num[1] != '-' && num[1] != '0'&&num[1]!=NULL)
	{
		printf("잘못된 입력 입니다.\n");
		return 7;//예외처리2
	}

	if (num[1] != '-')//한가지 이미지만 출력할 경우이다. 즉-가 없을 경우
	{
		if (b == 1 && c == 0) //10번째 이미지를 출력해주는 경우의 수이다.
		{
			for (y = 0; y < pic[9]->height; y++)
			{
				for (x = 0; x < pic[9]->width; x++)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (pic[9]->imgValue[y][x]) / 10);
					printf("■");
				}
				printf("\n");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			return 8;
		}
		else if (b <= t && b > 0)//그 외 나머지 경우를 출력해주는 경우이다.
		{
			z = num[0] - '0';

			for (y = 0; y < pic[z - 1]->height; y++)
			{
				for (x = 0; x < pic[z - 1]->width; x++)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (pic[z - 1]->imgValue[y][x]) / 10);
					printf("■");
				}
				printf("\n");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			return 8;
		}
		else if (b > t)//한 가지 수일땓수보은 수 입력시에는 예외처리를 해주었다.
		{
			printf("잘못된 입력범위 입니다.\n");
			return 7;
		}
	}
	else if (num[1] == '-')//한번에 여러장의 이미지를 출력하는 경우이다.
	{
		z = num[0] - '0';//z는 앞자리이고
		d = num[2] - '0';//d는 뒷자리의 처음 e는 둘째자리이다.
		e = num[3] - '0';
		
		if (d > t||(d*10+e)>t)//이미지 갯수보다 많은 범위의 출력시 오류처리이다.
		{
			printf("범위에 이미지가 없는 구간이 있습니다.\n");
			return 3;
		}

		if (d == 1 && e == 0)//뒷자리가 10일때와 아닐때를 나눠서 출력해주었다.
			w = 10;
		else if (d < 10 && d>0)
			w = num[2] - '0';

		for (a = z; a <= w; a++)//a-b라고 하면 그 범위의 모든 이미지를 출력해주는 경우이다.
		{
			for (y = 0; y < pic[a - 1]->height; y++)
			{
				for (x = 0; x < pic[a - 1]->width; x++)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (pic[a - 1]->imgValue[y][x]) / 10);
					printf("■");
				}
				printf("\n");
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	return 8;
}
int RemoveImgae(IMGMAT**pic, int t)
{
	int k, i, x, y;
	printf("삭제할 이미지 번호:");
	scanf("%d", &k);

	if (k> t)//할당된 것들보다 높은 수에 대한 예외처리이다.
	{
		printf("범위 밖의 입력입니다.\n");
		return 3;
	}
	else if (k > 0 && k <= t);//먼저 삭제할 칸을 비우고 한칸씩 앞으로 옮기는 방법이다.
	{
		for (i = 0; i < pic[k - 1]->height; i++)
			free(pic[k - 1]->imgValue[i]);//imgValue를 비워준다.
		free(pic[k - 1]->imgValue);

		free(pic[k - 1]);//멤버전체를 비우고
		pic[k - 1]->imgName = NULL;//이름을 초기화 후 비워준다.
		free(pic[k - 1]->imgName);
		for (i = k; i < t; i++)
		{
			pic[i - 1] = pic[i];//그 후 앞으로 한칸씩 이동시키는 경우이다.
		}
		printf("성공적으로 삭제하였습니다.\n");
		return 4;
	}
}
int zip(IMGMAT**pic, int t)
{
	FILE *outfile;
	int p, a, b, c = 1, d, x = 0, y = 0, w;
	int **room;
	char newname[30] = { NULL };

	printf("압축할 이미지 번호:");
	scanf("%d", &p);

	if (p > t || p < 1)//로드된 개수보다 높은 숫자의 번호 입력시 예외처리이다.
	{
		printf("잘못된 입력 범위입니다.\n");
		return 4;
	}

	if (p > 0 && p <= t)
	{
		w = strlen(pic[p - 1]->imgName) + 1;//NULL문자를 포함한 이름의 길이를 잡고
		strncpy(newname, pic[p - 1]->imgName, w - 5);//뒤에서부 NULL t x t . 이렇게 다섯글자전까지만 strncpy로 복사해서 newname에 붙이고 
		strcat(newname, "_c.txt");//strcat을 이용해서 _c.txt로 파일이름을 정해준다.
		w = strlen(newname);//마지막칸에 NULL을 넣기 위해 처리해준다.
		newname[w] = NULL;//압축파일에 _c를 붙여주기 위한 이름의 처리이다.

		outfile = fopen(newname, "w");

		room = (int**)malloc(sizeof(int*)*pic[p - 1]->height);
		for (y = 0; y < pic[p - 1]->height; y++)
			room[y] = (int*)malloc(sizeof(int)*pic[p - 1]->width);//room이라는 공간을 할당한다.(imgValue와 같음)

		fprintf(outfile, "%d %d 1\n", pic[p - 1]->height, pic[p - 1]->width);//압축시 compFlag값을 1로 해주고 나머지 정보는 그대로 넘긴다.

		for (y = 0; y < pic[p - 1]->height; y++)
		{
			for (x = 0; x < pic[p - 1]->width; x++)
			{
				room[y][x] = pic[p - 1]->imgValue[y][x] / 10;//양자화 시켜셔 imgValue들을 room에 집어넣는다.
			}
		}

		for (y = 0; y < pic[p - 1]->height; y++)
		{
			for (x = 0; x < pic[p - 1]->width; x++)
			{
				a = room[y][x];
				b = room[y][x + 1];//2글자씩 비교하면서 압축 과정을 거친다.
				if (x == pic[p - 1]->width - 1)//이 때 행의 끝까지 가면 그 다음 행의 처음픽셀부터 비교하기 위해 처리했다.
				{
					if (y != pic[p - 1]->height - 1)//특히 메모리의 끝부분에 가서 그 범위를 넘지 않기 위해 예외처리 해준다.
						b = room[y + 1][0];
				}

				if (a == b)//같을 경우에는 계속 c를 더해가면서 그 갯수를 세어주고
					c++;
				else if (a != b)//달라지는 순간 그것을 기록하고 다시1로 초기화해서 파일의 끝까지 세어준다.
				{
					fprintf(outfile, "%d %d ", a, c);
					c = 1;
				}
			}
		}
		printf("성공적으로 압축하였습니다.\n");
		printf("압축 파일명 : [%s]\n", newname);
	}
	fclose(outfile);
	free(room);
}
int mini(IMGMAT**pic, int t)
{
	FILE *file;
	char newname[30] = { NULL };//압축때와 마찬가지로 _r을 붙이기 위한 이름을 설정해준다.
	int p, w, a, b, c=1, d, x, y;
	int **room;

	printf("축소할 이미지 번호:");
	scanf("%d", &p);

	if (p > t || p < 1) //로드된 갯수보다 높은 숫자 입력시 예외처리이다.
	{
		printf("잘못된 입력 범위입니다.\n");
		return 4;
	}
	if (pic[p - 1]->height <= 20 || pic[p - 1]->width <= 20)//축소시 20x20이하크기로 못하게 예외처리했다.
	{
		printf("더이상 축소할 수 없는 크기입니다. (20x20)\n");
		return 4;
	}
	if (p > 0 && p <= t)
	{
		w = strlen(pic[p - 1]->imgName) + 1;
		strncpy(newname, pic[p - 1]->imgName, w - 5);
		strcat(newname, "_r.txt");
		w = strlen(newname);
		newname[w] = NULL;//압축때와 마찬가지로 이름을 형성해준다.

		file = fopen(newname, "w");
		fprintf(file, "%d %d %d \n", pic[p - 1]->height / 2, pic[p - 1]->width / 2, pic[p - 1]->compFlag);
		//축소 했기 때문에compFlag는 그대로 두고 height width를 반으로 줄인 것을 표현해준다.
		if (pic[p - 1]->compFlag == 1)//압축파일일 경우 축소시킨 후 다시 압축된 형식으로 해준다.
		{
			room = (int**)malloc(sizeof(int*)*pic[p - 1]->height);
			for (y = 0; y < pic[p - 1]->height; y++)
				room[y] = (int*)malloc(sizeof(int)*pic[p - 1]->width);
			//축소된 값저장을 위한 새로운 공간 할당.

			for (y = 0; y < pic[p - 1]->height; y = y + 2)
			{
				for (x = 0; x < pic[p - 1]->width; x = x + 2)
				{
					a = pic[p - 1]->imgValue[y][x];
					b = pic[p - 1]->imgValue[y][x + 1];
					c = pic[p - 1]->imgValue[y + 1][x];
					d = pic[p - 1]->imgValue[y + 1][x + 1];
					//우선순위순서대로a,b,c,d로 지정해주고

					if (a / 10 == b / 10 && b / 10 == c / 10 && c / 10 == d / 10 && d / 10 == a / 10)
						room[y][x] = a;
					//4:0일 경우 투표
					else if (b / 10 == c / 10 && c / 10 == d / 10 && b / 10 != a / 10)
						room[y][x] = b;
					else if (c / 10 == d / 10 && d / 10 == a / 10 && c / 10 != b / 10)
						room[y][x] = c;
					else if (b / 10 == d / 10 && d / 10 == a / 10 && b / 10 != c / 10)
						room[y][x] = b;
					else if (a / 10 == b / 10 && b / 10 == c / 10 && a / 10 != d / 10)
						room[y][x] = a;
					//3:0일 경우 투표
					else if (a / 10 == b / 10 && a / 10 != c / 10 && a / 10 != d / 10 && c / 10 != d / 10)
						room[y][x] = a;
					else if (a / 10 == c / 10 && a / 10 != b / 10 && a / 10 != d / 10 && b / 10 != d / 10)
						room[y][x] = a;
					else if (a / 10 == d / 10 && a / 10 != b / 10 && a / 10 != c / 10 && b / 10 != c / 10)
						room[y][x] = a;
					else if (b / 10 == c / 10 && b / 10 != a / 10 && b / 10 != d / 10 && a / 10 != d / 10)
						room[y][x] = b;
					else if (b / 10 == d / 10 && b / 10 != a / 10 && b / 10 != c / 10 && a / 10 != c / 10)
						room[y][x] = b;
					else if (c / 10 == d / 10 && c / 10 != a / 10 && c / 10 != b / 10 && a / 10 != b / 10)
						room[y][x] = c;
					//2:1:1일 경우 투표
					else if (a / 10 == b / 10 && c / 10 == d / 10 && a / 10 != c / 10)
						room[y][x] = a;
					else if (a / 10 == c / 10 && b / 10 == d / 10 && a / 10 != b / 10)
						room[y][x] = a;
					else if (a / 10 == d / 10 && b / 10 == c / 10 && a / 10 != b / 10)
						room[y][x] = a;
					//2:2일 경우 투표

					else if (a / 10 != b / 10 && a / 10 != c / 10 && a / 10 != d / 10 && b / 10 != c / 10 && b / 10 != d / 10 && c / 10 != d / 10)
						room[y][x] = a;
					//다 다를 경우는 우선순위에 의해서 a값을 준다.
				}
			}
			for (y = 0; y < pic[p - 1]->height / 2; y++)
			{
				for (x = 0; x < pic[p - 1]->width / 2; x++)
				{
					room[y][x] =room[y * 2][x * 2];
					//위에서는 축소 된 값들을 네칸중에서 왼칸위에만 넣었기 때문에 나머지 칸들에 대해서 축소를 위해서 모아준다.
				}
			}

			for (y = 0; y < pic[p - 1]->height/2; y++)
			{
				for (x = 0; x < pic[p - 1]->width/2; x++)
				{
					room[y][x] = room[y][x] / 10;
				}
			}
			c = 1;
			for (y = 0; y < pic[p - 1]->height/2; y++)
			{
				for (x = 0; x < pic[p - 1]->width/2; x++)
				{
					a = room[y][x];
					b = room[y][x + 1];
					if (x == pic[p - 1]->width - 1)
					{
						if (y != pic[p - 1]->height - 1)
							b = room[y + 1][0];
					}
						if (a == b)
							c++;
						else if (a != b)
						{
							fprintf(file, "%d %d ", a, c);
							c = 1;
						}//압축하는 것은 압축함수와 방법이 같다.
				}
			}
			printf("성공적으로 축소하였습니다.\n");
			printf("축소 파일명 : [%s]\n", newname);

		}
		else if (pic[p - 1]->compFlag == 0)//압축이 안되어있을 경우에는 그냥 축소만 시킨다. 위와 동일하다.
		{
			room = (int**)malloc(sizeof(int*)*pic[p - 1]->height);
			for (y = 0; y < pic[p - 1]->height; y++)
				room[y] = (int*)malloc(sizeof(int)*pic[p - 1]->width);

			for (y = 0; y < pic[p - 1]->height; y = y + 2)
			{
				for (x = 0; x < pic[p - 1]->width; x = x + 2)
				{
					a = pic[p - 1]->imgValue[y][x];
					b = pic[p - 1]->imgValue[y][x + 1];
					c = pic[p - 1]->imgValue[y + 1][x];
					d = pic[p - 1]->imgValue[y + 1][x + 1];
					//우선순위순서대로

					if (a / 10 == b / 10 && b / 10 == c / 10 && c / 10 == d / 10 && d / 10 == a / 10)
						room[y][x] = a;
					//4:0
					else if (b / 10 == c / 10 && c / 10 == d / 10 && b / 10 != a / 10)
						room[y][x] = b;
					else if (c / 10 == d / 10 && d / 10 == a / 10 && c / 10 != b / 10)
						room[y][x] = c;
					else if (b / 10 == d / 10 && d / 10 == a / 10 && b / 10 != c / 10)
						room[y][x] = b;
					else if (a / 10 == b / 10 && b / 10 == c / 10 && a / 10 != d / 10)
						room[y][x] = a;
					//3:0
					else if (a / 10 == b / 10 && a / 10 != c / 10 && a / 10 != d / 10 && c / 10 != d / 10)
						room[y][x] = a;
					else if (a / 10 == c / 10 && a / 10 != b / 10 && a / 10 != d / 10 && b / 10 != d / 10)
						room[y][x] = a;
					else if (a / 10 == d / 10 && a / 10 != b / 10 && a / 10 != c / 10 && b / 10 != c / 10)
						room[y][x] = a;
					else if (b / 10 == c / 10 && b / 10 != a / 10 && b / 10 != d / 10 && a / 10 != d / 10)
						room[y][x] = b;
					else if (b / 10 == d / 10 && b / 10 != a / 10 && b / 10 != c / 10 && a / 10 != c / 10)
						room[y][x] = b;
					else if (c / 10 == d / 10 && c / 10 != a / 10 && c / 10 != b / 10 && a / 10 != b / 10)
						room[y][x] = c;
					//2:1:1
					else if (a / 10 == b / 10 && c / 10 == d / 10 && a / 10 != c / 10)
						room[y][x] = a;
					else if (a / 10 == c / 10 && b / 10 == d / 10 && a / 10 != b / 10)
						room[y][x] = a;
					else if (a / 10 == d / 10 && b / 10 == c / 10 && a / 10 != b / 10)
						room[y][x] = a;
					//2:2

					else if (a / 10 != b / 10 && a / 10 != c / 10 && a / 10 != d / 10 && b / 10 != c / 10 && b / 10 != d / 10 && c / 10 != d / 10)
						room[y][x] = a;
					//1:1:1:1
				}
			}
				for (y = 0; y < pic[p - 1]->height / 2; y++)
				{
					for (x = 0; x < pic[p - 1]->width / 2; x++)
					{
						room[y][x] =room[y * 2][x * 2];
						fprintf(file, "%d ", room[y][x]);
					}
				}
			printf("성공적으로 축소하였습니다.\n");
			printf("축소 파일명 : [%s]\n", newname);
		}
	}fclose(file);
}
void EndPro(IMGMAT**pic, int t)
{
	int k,i;
	if(t!=0)
	for (k = 0; k < t; k++) 
	{
		for (i = 0; i < pic[k]->height; i++)
			free(pic[k]->imgValue[i]);

		free(pic[k]->imgValue);
		free(pic[k]);
		pic[k]->imgName = NULL;
		free(pic[k]->imgName);//프로그램 종료시 모든 구조체의 메모리할당을 해제한다.
	}
	else if (t == 0)
	{
		return 0;//만약 아무것도 없을 시 그냥 종료한다.
	}
}
//이번 어싸인에서 여러가지의 의미 없는 변수이름들(a,b,c,d,i,j등)은 대부분 카운트나 문자열 값을 int로 전환하기 위해 쓰였습니다.
//변수가 많아지다보니 변수명 설정이 어려워서... 죄송합니다.ㅠㅠ