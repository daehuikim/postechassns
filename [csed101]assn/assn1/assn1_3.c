#include<stdio.h>
int main(void)
{
	int a,b,c,d,e,f,bit1,bit2,bit3,bit4,bit5,result;
	//10������ �Է¹��� ������ 2������ ��Ÿ�� �� 2���� �ڸ��� ������ �����Ѵ�.
	printf("Input a 5-bit binary number:");
	scanf("%d",&a);
	//scanf�Լ���a���ٰ� 10���� ���� �Է¹޴´�.

	bit1=a/10000; 	//a��10��4�������� ������(1or0)�� bit1�� �ְ�
	b=a%10000; 		//�� �������� b�� �ִ´�
	bit2=b/1000;	//���������� b�� 10�� 3�������� ������(1or0)�� bit2�� �ְ�
	c=b%1000;		//�� �������� c�� �־� 10�� 0�±��� �ݺ����ش�
	bit3=c/100;		
	d=c%100;		
	bit4=d/10;		
	e=d%10;			
	bit5=e/1;
	f=e%1;

	result = 2*2*2*2*bit1 + 2*2*2*bit2 + 2*2*bit3 + 2*bit4 + 1*bit5;
	//bit n(n=1~5)�� �Էµ� ��(1or0)�� 2���� �ڸ����� ���� ��� �����ش�.
	printf("the binary number %d is a decimal number %d\n",a,result);
	//�� ������� ������ش�
	return 0;
}
