#include<stdio.h>
#include<stdlib.h>

int main()
{
	int array[5] = {123, 77, 24, 14, 48};
	int i;
	int result = 0;
	for (i = 0; i < 5; ++i) {
		result += array[i];
	}
	printf("%d\n", result);
}
