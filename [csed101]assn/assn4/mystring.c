#include<stdio.h>
#include"mystring.h"

int main()
{
	printf("%d\n", mystrlen("cs101"));
	char str[256];
	printf("%s\n", mystrcpy(str, "Good Day"));
	printf("%s\n", mystrcpy(str, "Hello"));
	printf("%d\n", mystrcmp("csed101", "csed103"));
	printf("%d\n", mystrcmp("csed", "Csed"));
	printf("%d\n", mystrcmp("csed", "cse"));
	printf("%d\n", mystrcmp("csed", "csed103"));
	char str1[256] = "Hello";
	mystrcat(str1, ", World");
	printf("%s\n", str1);
	return 0;
}
int mystrlen(char *str)
{
	int i;

	for (i = 0;; i++)
		if (str[i] == NULL)
			break;
	return i;
}

char *mystrcpy(char *toStr, char *fromStr)
{
	toStr = fromStr;
	return toStr;
}

int mystrcmp(char *str1, char *str2)
{
	int i,j,k;

	for(j=0;;j++)
		if (str1[j] == NULL)
			break;
	for (k = 0;; k++)
		if (str2[k] == NULL)
			break;

	if (j > k)
		return 1;
	else if (j < k)
		return -1;

	for (i = 0; i < j || i < k; i++)
	{
		if (str1[i] == str2[i])
			i++;
		else if (str1[i] < str2[i])
			return -1;
		else if (str1[i] > str2[i])
			return 1;
	}
	return 0;
}

char *mystrcat(char *str1, char *str2)
{
	int i,k;
	for (i = 0;; i++)
		if (str1[i] == NULL)
			break;

	for ( k = 0;;k++)
	{
		str1[i+k] = str2[k];
		if (str2[k] == NULL)
			break;
	}
	return str1;
}
