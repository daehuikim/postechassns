#include <stdio.h>
#include <stdlib.h>//�� �ΰ��� �ʼ� ���̺귯��
#include <string.h>//���ڿ� �����Լ� ��� ���
#include <Windows.h>//��¿� �ʿ��� ���

#define MAX_LOAD_IMG_SIZE 10//����ü ������ �迭�� ���� ����
typedef struct
{
	int width; // �̹����� ����
	int height; // �̹����� ����
	int compFlag; // ������ �Ͽ��°� 0: No, 1: Yes
	char *imgName; // �̹����� �̸�
	int **imgValue; // �̹����� �ȼ� ����
} IMGMAT;//����ü�� �̸�(�̹��� ����)

void printIndex(IMGMAT **pic, int t);//�޴�1��
int loadImage(IMGMAT **pic, int t);  //�޴�2��
int printImage(IMGMAT **pic, int t); //�޴�3��
int RemoveImgae(IMGMAT**pic, int t); //�޴�4��
int zip(IMGMAT**pic, int t);        //�޴�5��
int mini(IMGMAT**pic, int t);       //�޴�6��
void EndPro(IMGMAT**pic, int t);	 //�޴�0��

int main()
{
	IMGMAT *pic[MAX_LOAD_IMG_SIZE];
	int t = 0, m, n, con = 1, i, o = 0,b;
	char check[256] = { NULL };
	system("mode con:cols=170 lines=95");

	while (1)
	{//�Ź� �޴����� ����Ѵ�.
		printf("====================================\n");
		printf("[1] �̹��� ��� ����\n");
		printf("[2] �̹��� �ε�\n");
		printf("[3] �̹��� ���\n");
		printf("[4] �̹��� ����\n");
		printf("[5] �̹��� ����\n");
		printf("[6] �̹��� ���\n");
		printf("[0] ����\n");
		printf("====================================\n");
		printf("�޴� ��ȣ �Է�:");
		scanf("%s", check);

		if (check[0] == '1'&&check[1]==NULL)//1�̿��� ��°��� �̰��� ���� ���ϰ� �� ���Ŀ��� �����ߴ�.
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
			t--;//t�� �̹��� ���� �����̰� ������ - �ε��+�Ѵ�.
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
			printf("���α׷��� ����Ǿ����ϴ�.\n");
			return 0;
		}
		else //0123456 �� �ƴ� �̻󿡴� �߸��� ������ �˷��ش�.
		{
			printf("�Է¹��� ���� ���� �ƴմϴ�.\n");
		}
	}
}//main�Լ������� �޴� ��°� ���α׷� ������ �Ѵ�.
void printIndex(IMGMAT **pic, int t)
{//����ü �迭�� �� ������ �޾Ƽ� �̹��� ����� �̸��� ����Ѵ�.
	int i;
	if (t == 0)//�ƹ� �̹����� ���� ����� ����ó���̴�.
	{
		printf("�ε��� �̹����� �����ϴ�.\n");
	}
	else//�̹����� ���� ��쿡�� t(�ε�� �̹��� ����)��ŭ ���� ������� ������ش�.
	{
		for (i = 1; i <= t; i++)
			printf("[%d]�� �̹��� �̸�: %s\n", i, pic[i - 1]->imgName);
	}
}
int loadImage(IMGMAT **pic, int t)
{
	int x, y, a, b, c, d, h = 0, l, k;
	int n, m;

	if (t >= 10)
	{
		printf("�ε��� �� �ִ� ������ �Ѿ����ϴ�.\n");
		return 2;
	}
	pic[t] = (IMGMAT*)malloc(sizeof(IMGMAT));//���� ����ü �迭�� ��ü�� �޸𸮸� �����Ҵ��Ѵ�.
	pic[t]->imgName = (char*)malloc(sizeof(char) * 30);//�׸��� �̹��� ���Ӹ�ŭ�� �޸𸮸� �����Ҵ��Ѵ�.
	printf("���� �̹��� �̸�:");
	scanf("%s", pic[t]->imgName);

	pic[t]->imgName = (char*)realloc(pic[t]->imgName, sizeof(char)*(strlen(pic[t]->imgName) + 1));//�� �� ���� �̸���ŭ realloc�Ѵ�.
	FILE *infile;
	infile = fopen(pic[t]->imgName, "r");//txt������ �о�鿩�� �޸𸮿� �����Ѵ�.
	if (infile == NULL)
	{
		printf("������ �����ϴ�.\n");
		return 2;
	}
	else
	{
		fscanf(infile, "%d %d %d \n", &(pic[t]->height), &(pic[t]->width), &(pic[t]->compFlag));

		if (pic[t]->compFlag == 0)//������� ���� ������ �ε���������, ������ �迭�� �����Ҵ��ϰ� �� �Ҵ��� ĭ�� ������ ����ִ´�.
		{
			pic[t]->imgValue = (int**)malloc(sizeof(int*)*pic[t]->height);

			for (y = 0; y < pic[t]->height; y++)
			{
				pic[t]->imgValue[y] = (int*)malloc(sizeof(int)*pic[t]->width);
				for (x = 0; x < pic[t]->width; x++)
					fscanf(infile, "%d ", &(pic[t]->imgValue[y][x]));
			}
			printf("[%s]�� ���������� �ε��Ͽ����ϴ�.\n", pic[t]->imgName);
			return 1;
		}

		else if (pic[t]->compFlag == 1)//����� ������ ��� 2���ھ� �����鼭 10�� ������ ������ imgValue�� ����־ ����ȭ�� ���� ������ָ� �ε��Ѵ�.
		{
			pic[t]->imgValue = (int**)malloc(sizeof(int*)*pic[t]->height);
			for (y = 0; y < pic[t]->height; y++)
				pic[t]->imgValue[y] = (int*)malloc(sizeof(int)*pic[t]->width);
			//value�� ������ �Ҵ��Ѵ�.
			m = 0;
			for (y = 0; y < pic[t]->height; y++)//���� ������ �����鼭
				for (x = 0; x < pic[t]->width; x++)
				{
					if (m == 0)
						fscanf(infile, "%d %d ", &n, &m);
					pic[t]->imgValue[y][x] = n * 10;
					m--;
				}
		}
		printf("[%s]�� ���������� �ε��Ͽ����ϴ�.\n", pic[t]->imgName);
		return 1;
	}
}
int printImage(IMGMAT **pic, int t)
{
	int x, y, z, w, a, b, c, d, e;
	char num[256] = { NULL };
	printf("����� �̹��� ��ȣ:ex<2or2-4>");
	scanf("%s", num);
	//1-10������ �Է��� �� �ֱ� ������ 5ĭ¥�� ���ڿ��� ������ �� -�� �Էµ� ���� �ƴѰ�쿡 ���� ������ �����Ѵ�.
	b = num[0] - '0';
	c = num[1] - '0';
	
	if (b < 1 || (c >= 1 && b >= 0))
	{
		printf("�߸��� �Է¹��� �Դϴ�.\n");
		return 7;//���ڹ����� ��� ����ó���̴�.
	}

	if (num[1] != '-' && num[1] != '0'&&num[1]!=NULL)
	{
		printf("�߸��� �Է� �Դϴ�.\n");
		return 7;//����ó��2
	}

	if (num[1] != '-')//�Ѱ��� �̹����� ����� ����̴�. ��-�� ���� ���
	{
		if (b == 1 && c == 0) //10��° �̹����� ������ִ� ����� ���̴�.
		{
			for (y = 0; y < pic[9]->height; y++)
			{
				for (x = 0; x < pic[9]->width; x++)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (pic[9]->imgValue[y][x]) / 10);
					printf("��");
				}
				printf("\n");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			return 8;
		}
		else if (b <= t && b > 0)//�� �� ������ ��츦 ������ִ� ����̴�.
		{
			z = num[0] - '0';

			for (y = 0; y < pic[z - 1]->height; y++)
			{
				for (x = 0; x < pic[z - 1]->width; x++)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (pic[z - 1]->imgValue[y][x]) / 10);
					printf("��");
				}
				printf("\n");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			return 8;
		}
		else if (b > t)//�� ���� ���ϋi������ �� �Է½ÿ��� ����ó���� ���־���.
		{
			printf("�߸��� �Է¹��� �Դϴ�.\n");
			return 7;
		}
	}
	else if (num[1] == '-')//�ѹ��� �������� �̹����� ����ϴ� ����̴�.
	{
		z = num[0] - '0';//z�� ���ڸ��̰�
		d = num[2] - '0';//d�� ���ڸ��� ó�� e�� ��°�ڸ��̴�.
		e = num[3] - '0';
		
		if (d > t||(d*10+e)>t)//�̹��� �������� ���� ������ ��½� ����ó���̴�.
		{
			printf("������ �̹����� ���� ������ �ֽ��ϴ�.\n");
			return 3;
		}

		if (d == 1 && e == 0)//���ڸ��� 10�϶��� �ƴҶ��� ������ ������־���.
			w = 10;
		else if (d < 10 && d>0)
			w = num[2] - '0';

		for (a = z; a <= w; a++)//a-b��� �ϸ� �� ������ ��� �̹����� ������ִ� ����̴�.
		{
			for (y = 0; y < pic[a - 1]->height; y++)
			{
				for (x = 0; x < pic[a - 1]->width; x++)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (pic[a - 1]->imgValue[y][x]) / 10);
					printf("��");
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
	printf("������ �̹��� ��ȣ:");
	scanf("%d", &k);

	if (k> t)//�Ҵ�� �͵麸�� ���� ���� ���� ����ó���̴�.
	{
		printf("���� ���� �Է��Դϴ�.\n");
		return 3;
	}
	else if (k > 0 && k <= t);//���� ������ ĭ�� ���� ��ĭ�� ������ �ű�� ����̴�.
	{
		for (i = 0; i < pic[k - 1]->height; i++)
			free(pic[k - 1]->imgValue[i]);//imgValue�� ����ش�.
		free(pic[k - 1]->imgValue);

		free(pic[k - 1]);//�����ü�� ����
		pic[k - 1]->imgName = NULL;//�̸��� �ʱ�ȭ �� ����ش�.
		free(pic[k - 1]->imgName);
		for (i = k; i < t; i++)
		{
			pic[i - 1] = pic[i];//�� �� ������ ��ĭ�� �̵���Ű�� ����̴�.
		}
		printf("���������� �����Ͽ����ϴ�.\n");
		return 4;
	}
}
int zip(IMGMAT**pic, int t)
{
	FILE *outfile;
	int p, a, b, c = 1, d, x = 0, y = 0, w;
	int **room;
	char newname[30] = { NULL };

	printf("������ �̹��� ��ȣ:");
	scanf("%d", &p);

	if (p > t || p < 1)//�ε�� �������� ���� ������ ��ȣ �Է½� ����ó���̴�.
	{
		printf("�߸��� �Է� �����Դϴ�.\n");
		return 4;
	}

	if (p > 0 && p <= t)
	{
		w = strlen(pic[p - 1]->imgName) + 1;//NULL���ڸ� ������ �̸��� ���̸� ���
		strncpy(newname, pic[p - 1]->imgName, w - 5);//�ڿ����� NULL t x t . �̷��� �ټ������������� strncpy�� �����ؼ� newname�� ���̰� 
		strcat(newname, "_c.txt");//strcat�� �̿��ؼ� _c.txt�� �����̸��� �����ش�.
		w = strlen(newname);//������ĭ�� NULL�� �ֱ� ���� ó�����ش�.
		newname[w] = NULL;//�������Ͽ� _c�� �ٿ��ֱ� ���� �̸��� ó���̴�.

		outfile = fopen(newname, "w");

		room = (int**)malloc(sizeof(int*)*pic[p - 1]->height);
		for (y = 0; y < pic[p - 1]->height; y++)
			room[y] = (int*)malloc(sizeof(int)*pic[p - 1]->width);//room�̶�� ������ �Ҵ��Ѵ�.(imgValue�� ����)

		fprintf(outfile, "%d %d 1\n", pic[p - 1]->height, pic[p - 1]->width);//����� compFlag���� 1�� ���ְ� ������ ������ �״�� �ѱ��.

		for (y = 0; y < pic[p - 1]->height; y++)
		{
			for (x = 0; x < pic[p - 1]->width; x++)
			{
				room[y][x] = pic[p - 1]->imgValue[y][x] / 10;//����ȭ ���Ѽ� imgValue���� room�� ����ִ´�.
			}
		}

		for (y = 0; y < pic[p - 1]->height; y++)
		{
			for (x = 0; x < pic[p - 1]->width; x++)
			{
				a = room[y][x];
				b = room[y][x + 1];//2���ھ� ���ϸ鼭 ���� ������ ��ģ��.
				if (x == pic[p - 1]->width - 1)//�� �� ���� ������ ���� �� ���� ���� ó���ȼ����� ���ϱ� ���� ó���ߴ�.
				{
					if (y != pic[p - 1]->height - 1)//Ư�� �޸��� ���κп� ���� �� ������ ���� �ʱ� ���� ����ó�� ���ش�.
						b = room[y + 1][0];
				}

				if (a == b)//���� ��쿡�� ��� c�� ���ذ��鼭 �� ������ �����ְ�
					c++;
				else if (a != b)//�޶����� ���� �װ��� ����ϰ� �ٽ�1�� �ʱ�ȭ�ؼ� ������ ������ �����ش�.
				{
					fprintf(outfile, "%d %d ", a, c);
					c = 1;
				}
			}
		}
		printf("���������� �����Ͽ����ϴ�.\n");
		printf("���� ���ϸ� : [%s]\n", newname);
	}
	fclose(outfile);
	free(room);
}
int mini(IMGMAT**pic, int t)
{
	FILE *file;
	char newname[30] = { NULL };//���ට�� ���������� _r�� ���̱� ���� �̸��� �������ش�.
	int p, w, a, b, c=1, d, x, y;
	int **room;

	printf("����� �̹��� ��ȣ:");
	scanf("%d", &p);

	if (p > t || p < 1) //�ε�� �������� ���� ���� �Է½� ����ó���̴�.
	{
		printf("�߸��� �Է� �����Դϴ�.\n");
		return 4;
	}
	if (pic[p - 1]->height <= 20 || pic[p - 1]->width <= 20)//��ҽ� 20x20����ũ��� ���ϰ� ����ó���ߴ�.
	{
		printf("���̻� ����� �� ���� ũ���Դϴ�. (20x20)\n");
		return 4;
	}
	if (p > 0 && p <= t)
	{
		w = strlen(pic[p - 1]->imgName) + 1;
		strncpy(newname, pic[p - 1]->imgName, w - 5);
		strcat(newname, "_r.txt");
		w = strlen(newname);
		newname[w] = NULL;//���ට�� ���������� �̸��� �������ش�.

		file = fopen(newname, "w");
		fprintf(file, "%d %d %d \n", pic[p - 1]->height / 2, pic[p - 1]->width / 2, pic[p - 1]->compFlag);
		//��� �߱� ������compFlag�� �״�� �ΰ� height width�� ������ ���� ���� ǥ�����ش�.
		if (pic[p - 1]->compFlag == 1)//���������� ��� ��ҽ�Ų �� �ٽ� ����� �������� ���ش�.
		{
			room = (int**)malloc(sizeof(int*)*pic[p - 1]->height);
			for (y = 0; y < pic[p - 1]->height; y++)
				room[y] = (int*)malloc(sizeof(int)*pic[p - 1]->width);
			//��ҵ� �������� ���� ���ο� ���� �Ҵ�.

			for (y = 0; y < pic[p - 1]->height; y = y + 2)
			{
				for (x = 0; x < pic[p - 1]->width; x = x + 2)
				{
					a = pic[p - 1]->imgValue[y][x];
					b = pic[p - 1]->imgValue[y][x + 1];
					c = pic[p - 1]->imgValue[y + 1][x];
					d = pic[p - 1]->imgValue[y + 1][x + 1];
					//�켱�����������a,b,c,d�� �������ְ�

					if (a / 10 == b / 10 && b / 10 == c / 10 && c / 10 == d / 10 && d / 10 == a / 10)
						room[y][x] = a;
					//4:0�� ��� ��ǥ
					else if (b / 10 == c / 10 && c / 10 == d / 10 && b / 10 != a / 10)
						room[y][x] = b;
					else if (c / 10 == d / 10 && d / 10 == a / 10 && c / 10 != b / 10)
						room[y][x] = c;
					else if (b / 10 == d / 10 && d / 10 == a / 10 && b / 10 != c / 10)
						room[y][x] = b;
					else if (a / 10 == b / 10 && b / 10 == c / 10 && a / 10 != d / 10)
						room[y][x] = a;
					//3:0�� ��� ��ǥ
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
					//2:1:1�� ��� ��ǥ
					else if (a / 10 == b / 10 && c / 10 == d / 10 && a / 10 != c / 10)
						room[y][x] = a;
					else if (a / 10 == c / 10 && b / 10 == d / 10 && a / 10 != b / 10)
						room[y][x] = a;
					else if (a / 10 == d / 10 && b / 10 == c / 10 && a / 10 != b / 10)
						room[y][x] = a;
					//2:2�� ��� ��ǥ

					else if (a / 10 != b / 10 && a / 10 != c / 10 && a / 10 != d / 10 && b / 10 != c / 10 && b / 10 != d / 10 && c / 10 != d / 10)
						room[y][x] = a;
					//�� �ٸ� ���� �켱������ ���ؼ� a���� �ش�.
				}
			}
			for (y = 0; y < pic[p - 1]->height / 2; y++)
			{
				for (x = 0; x < pic[p - 1]->width / 2; x++)
				{
					room[y][x] =room[y * 2][x * 2];
					//�������� ��� �� ������ ��ĭ�߿��� ��ĭ������ �־��� ������ ������ ĭ�鿡 ���ؼ� ��Ҹ� ���ؼ� ����ش�.
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
						}//�����ϴ� ���� �����Լ��� ����� ����.
				}
			}
			printf("���������� ����Ͽ����ϴ�.\n");
			printf("��� ���ϸ� : [%s]\n", newname);

		}
		else if (pic[p - 1]->compFlag == 0)//������ �ȵǾ����� ��쿡�� �׳� ��Ҹ� ��Ų��. ���� �����ϴ�.
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
					//�켱�����������

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
			printf("���������� ����Ͽ����ϴ�.\n");
			printf("��� ���ϸ� : [%s]\n", newname);
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
		free(pic[k]->imgName);//���α׷� ����� ��� ����ü�� �޸��Ҵ��� �����Ѵ�.
	}
	else if (t == 0)
	{
		return 0;//���� �ƹ��͵� ���� �� �׳� �����Ѵ�.
	}
}
//�̹� ����ο��� ���������� �ǹ� ���� �����̸���(a,b,c,d,i,j��)�� ��κ� ī��Ʈ�� ���ڿ� ���� int�� ��ȯ�ϱ� ���� �������ϴ�.
//������ �������ٺ��� ������ ������ �������... �˼��մϴ�.�Ф�