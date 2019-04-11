#include<stdio.h>
int main(void)
{
	int a,b,c,answer;
	//직육면체의 가로 세로 높이와 결과값을 변수 지정한다.
	printf("Input width, height, depth:");
	scanf("%d %d %d",&a,&b,&c);
	//scanf 함수를 이용해 %d와 &를 이용해서 변수에다 정수형 자료를 입력받는다.
	answer=4*(a+b+c-6);
	/*직육면체 한 모서리에서 꼭짓점 부분에 있는 블럭2개를 제외하고 모서리
	위에 있는 블럭은 모두2면이 칠해져 있으므로 이 점을 고려하면 모서리 길이에서
	2를 뺀 만큼을 모두 더한 것이 구하려는 값인데 길이가 같은 모서리가 4개씩
	있으므로 위의 식을 활용할 수 있다.*/
	printf("Result: %d\n",answer);
	return 0;

}
