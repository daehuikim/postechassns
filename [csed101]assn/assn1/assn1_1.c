#include<stdio.h>
int main()
{
	char letter1, letter2, letter3;
	//입력 받을 대문자를 문자형으로 변수를 지정함
	printf("Input your initials with white space:");
	scanf("%c %c %c", &letter1, &letter2, &letter3);
	/* scanf로 받을 때 변수가 문자형이기 때문에 %c를 이용하고 &로 변수의
	   주소에다 값을 입력 받는다.*/
	printf("ASCII code of your input:%d %d %d\n",letter1,letter2,letter3);
	//입력받은 대문자의 아스키 코드값을 보여주기 위해%d로 출력한다.
	letter1=letter1+32;
	letter2=letter2+32; 	//대문자를 소문자로 출력하기 위해서
	letter3=letter3+32;		//ASCII코드 값을 참조해 각각 32를 더해준다.
	printf("converted output:%c %c %c\n",letter1,letter2,letter3);
	//소문자로 변환된 문자들을 %c를 이용해서 출력해준다.
	return 0;

}
