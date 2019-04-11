#include<stdio.h>
#include<math.h>  //���� ����� �����ϱ� ���ؼ� math.h�� ���Խ�Ų��.

float cal_area(int, int, int, int, int, int);
int is_ccw(int, int, int, int, int, int);

int main()
{
	int i = 4, num = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0, x4 = 0, y4 = 0, ccw1 = 1, ccwcheck = 1;
	float area1 = 0, totarea = 0;  //���� �Է¹��� xy��ǥ��� ��꿡 �ʿ��� �������� �����ߴ�.
	while (1)
	{
		printf("Enter the number of vertices (->2): "); //���� �� ������ �Է¹ް� 2���ϳ� 100�̻��� ��� �ٽ� �Է¹޵��� �ݺ����� �����Ѵ�.
		scanf("%d", &num);
		if (num <= 2 || num > 100)
		{
			printf("The number of veritices should be more than 2\n");
		}
		else break;
		}
	if (num == 3)  //3������ ��� 3���� ������ �ް� ���̸� ����Ѵ�.
	{
		printf("Input the value x and y of P1:");
		scanf("%d %d", &x1, &y1);
		printf("Input the value x and y of P2:");
		scanf("%d %d", &x2, &y2);
		printf("Input the value x and y of P3:");
		scanf("%d %d", &x3, &y3);
		area1 = cal_area(x1, x2, x3, y1, y2, y3);
		printf("area of 3-polygon(convex) :%.2f", area1);
	}
	else if (num >= 4) //4���� �̻��� ��� ������ ���� �������̹Ƿ� ��4���� ���� ������ ����Ѵ�.
	{
		for (i = 1; i <= num; i++)
		{
			
			x3 = x2, y3 = y2; //Ư�� �̶� ù��° ���� x4,y4�� �Ѱ��� ���� ������ ������ ��� �����ذ��鼭 �� �������� ������ �Ѱܰ��� ����� �����Ѵ�.
			x2 = x1, y2 = y1;
			printf("Input the value x and y of P%d:", i);
			scanf("%d %d", &x1, &y1);
			if (i == 1)
			{
				x4 = x1, y4 = y1;
			}
			if (i >= 3)
			{
				ccw1 = is_ccw(x3, x2, x1, y3, y2, y1);
				area1 = cal_area(x4, x2, x1, y4, y2, y1);
			}
			totarea = totarea + area1;  //�ݺ����ȿ��� �ٰ����� �ﰢ������ ������ ��� ���ذ��� ����� ���Ѵ�.
			ccwcheck = ccwcheck*ccw1;  //�ݺ����ȿ��� ���������� ������ ���� 180���̻� ��, �������� ��ȣ�� �ٲ��� return���� �޸��Ͽ� �Ǻ��Ѵ�.
			if (ccwcheck == 2)
			{
				printf("Concave polygon!\n"); //�����ϰ�� ���1, �ѹ��̶� ������ ���2�� return�Ͽ� �ѹ��̶� ����ٰ������� �Ǻ��� ��� ccwcheck�� 2�� ���� �������������ȴ�.
				break;
			}
		}
		if (ccwcheck == 1)
		{
			printf("Area of %d-Polygon(convex):%.2f\n", num, totarea); //�ٰ����� ���ϴٰ����� ��� ���̸� ��Ÿ���ش�.
		}
	}

	return 0;
}
float cal_area(int x1, int x2, int x3, int y1, int y2, int y3)
{
	int sum;
	sum = abs((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1)); //������ �޾ƿͼ� �ﰢ���� ���̸� ���Ѵ�.(�� ��, �ٰ����� �ﰢ������ ���� ���� ������� ��.)
	return sum / (2.0);
}
int is_ccw(int x1, int x2, int x3, int y1, int y2, int y3)
{
	int ccw;
	ccw = (x2 - x1)*(y3 - y2) - (x3 - x2)*(y2 - y1); //�������� ���ؼ� ��ȣ�� �ѹ��̶� ������ �� ��� �������� �Ǵ��Ѵ�.(���0�̰ų� ����ϰ�� ���� 180���� ���� ����.)
	if (ccw > 0 || ccw == 0)
	{
		return 1;
	}
	else if (ccw < 0)
	{
		return 2;
	}
}