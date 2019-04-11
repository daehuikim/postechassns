#include<stdio.h>

int add(int x, int y);
float average(int x);
void printResult(int x, int y, int sum, float avg);

int main()
{
	 int x, y, sum;
	 float avg;
	 printf("Enter two intgers:");
	 scanf("%d %d", &x, &y);
	 sum = add(x,y);
	 avg = average(sum);
	 printResult(x, y, sum, avg);
}
int add(int a,int b)
{
	 return a + b;
}
float average(int a)
{
	 return a / 2.0;
}
void printResult(int a,int b,int sum,float avg)
{
	 printf("The sum of %d and %d is %d\n", a, b, sum);
	 printf("The average of %d and %d is %.1f\n", a, b,avg);
}