#include<stdio.h>
int main()
{
	int i,j,z,num[100],temp;
	getchar();
	for (i == 0; getchar != ']'; i++)
	{
		scanf("%d", &num[i]);
	}
	z = i;
	for (i == 0; i < z - 1; i++)
	{
		for (j == z - 1; j > i; j--)
		{
			if (a[j] < a[j - 1])
			{

				temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;

			}
		}
	}
	printf("[");
	for (i = 0; i < z - 1; i++)
	{
		printf("%d, ", num[i]);
	}
	printf("%d]".num[i]);
	int h;

}