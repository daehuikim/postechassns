#include<stdio.h>
#include<math.h>  //절댓값 계산을 포함하기 위해서 math.h를 포함시킨다.

float cal_area(int, int, int, int, int, int);
int is_ccw(int, int, int, int, int, int);

int main()
{
	int i = 4, num = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0, x4 = 0, y4 = 0, ccw1 = 1, ccwcheck = 1;
	float area1 = 0, totarea = 0;  //각각 입력받을 xy좌표들과 계산에 필요한 변수들을 지정했다.
	while (1)
	{
		printf("Enter the number of vertices (->2): "); //시작 시 변수를 입력받고 2이하나 100이상일 경우 다시 입력받도록 반복문을 설정한다.
		scanf("%d", &num);
		if (num <= 2 || num > 100)
		{
			printf("The number of veritices should be more than 2\n");
		}
		else break;
		}
	if (num == 3)  //3각형일 경우 3점에 변수를 받고 넓이를 계산한다.
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
	else if (num >= 4) //4각형 이상의 경우 변수의 값이 한정적이므로 총4개의 점을 가지고 계산한다.
	{
		for (i = 1; i <= num; i++)
		{
			
			x3 = x2, y3 = y2; //특히 이때 첫번째 점을 x4,y4에 넘겨준 다음 나머지 값들은 계속 갱신해가면서 즉 앞쪽으로 값들을 넘겨가며 계산을 시행한다.
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
			totarea = totarea + area1;  //반복문안에서 다각형을 삼각형으로 나눠서 계속 더해가는 방식을 택한다.
			ccwcheck = ccwcheck*ccw1;  //반복문안에서 각변마다의 외적을 통해 180도이상 즉, 외적값의 부호가 바뀔경우 return값을 달리하여 판별한다.
			if (ccwcheck == 2)
			{
				printf("Concave polygon!\n"); //볼록일경우 계속1, 한번이라도 오목일 경우2를 return하여 한번이라도 오목다각형으로 판별될 경우 ccwcheck에 2가 들어가고 오목으로판정된다.
				break;
			}
		}
		if (ccwcheck == 1)
		{
			printf("Area of %d-Polygon(convex):%.2f\n", num, totarea); //다각형이 볼록다각형일 경우 넓이를 나타내준다.
		}
	}

	return 0;
}
float cal_area(int x1, int x2, int x3, int y1, int y2, int y3)
{
	int sum;
	sum = abs((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1)); //변수를 받아와서 삼각형의 넓이를 구한다.(이 때, 다각형을 삼각형으로 나눈 것을 기반으로 함.)
	return sum / (2.0);
}
int is_ccw(int x1, int x2, int x3, int y1, int y2, int y3)
{
	int ccw;
	ccw = (x2 - x1)*(y3 - y2) - (x3 - x2)*(y2 - y1); //외적값을 통해서 부호가 한번이라도 음수가 될 경우 오목으로 판단한다.(계속0이거나 양수일경우 각이 180도가 넘지 않음.)
	if (ccw > 0 || ccw == 0)
	{
		return 1;
	}
	else if (ccw < 0)
	{
		return 2;
	}
}