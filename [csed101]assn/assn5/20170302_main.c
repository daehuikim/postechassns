#include<stdio.h>
#include"calc.h"


int main()
{
	int a, b,add1,sub1,mul1,div1;
	printf("Enter two integers : ");
	scanf("%d %d", &a, &b);
	
	add1 = add(a, b);
	sub1 = sub(a, b);
	mul1 = mul(a, b);
	div1 = div(a, b);

	printf("%d + %d = %d\n", a, b, add1);
	printf("%d - %d = %d\n", a, b, sub1);
	printf("%d * %d = %d\n", a, b, mul1);
	printf("%d / %d = %d\n", a, b, div1);

	return 0;
}
