#include<stdio.h>
int main()
{
	char letter1, letter2, letter3;
	//�Է� ���� �빮�ڸ� ���������� ������ ������
	printf("Input your initials with white space:");
	scanf("%c %c %c", &letter1, &letter2, &letter3);
	/* scanf�� ���� �� ������ �������̱� ������ %c�� �̿��ϰ� &�� ������
	   �ּҿ��� ���� �Է� �޴´�.*/
	printf("ASCII code of your input:%d %d %d\n",letter1,letter2,letter3);
	//�Է¹��� �빮���� �ƽ�Ű �ڵ尪�� �����ֱ� ����%d�� ����Ѵ�.
	letter1=letter1+32;
	letter2=letter2+32; 	//�빮�ڸ� �ҹ��ڷ� ����ϱ� ���ؼ�
	letter3=letter3+32;		//ASCII�ڵ� ���� ������ ���� 32�� �����ش�.
	printf("converted output:%c %c %c\n",letter1,letter2,letter3);
	//�ҹ��ڷ� ��ȯ�� ���ڵ��� %c�� �̿��ؼ� ������ش�.
	return 0;

}
