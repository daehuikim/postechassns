#include<stdio.h>
int main(void)
{
	int a,b,c,d,e,f,bit1,bit2,bit3,bit4,bit5,result;
	//10진수로 입력받을 변수와 2진수로 나타내 줄 2진수 자리의 변수를 지정한다.
	printf("Input a 5-bit binary number:");
	scanf("%d",&a);
	//scanf함수로a에다가 10진수 값을 입력받는다.

	bit1=a/10000; 	//a를10의4제곱으로 나눈값(1or0)을 bit1에 넣고
	b=a%10000; 		//그 나머지를 b에 넣는다
	bit2=b/1000;	//마찬가지로 b를 10의 3제곱으로 나눈값(1or0)을 bit2에 넣고
	c=b%1000;		//그 나머지를 c에 넣어 10의 0승까지 반복해준다
	bit3=c/100;		
	d=c%100;		
	bit4=d/10;		
	e=d%10;			
	bit5=e/1;
	f=e%1;

	result = 2*2*2*2*bit1 + 2*2*2*bit2 + 2*2*bit3 + 2*bit4 + 1*bit5;
	//bit n(n=1~5)에 입력된 값(1or0)과 2진수 자릿수를 맞춰 모두 더해준다.
	printf("the binary number %d is a decimal number %d\n",a,result);
	//그 결과값을 출력해준다
	return 0;
}
