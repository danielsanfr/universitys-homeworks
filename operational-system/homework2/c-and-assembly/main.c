#include<stdio.h>

/*
 * Returns 1 if the num is prime; otherwise returns 0
 */
extern int prime(int num);

int main()
{
	int ret = prime(13);
	printf("%d\n", ret);
	return 0;
}
