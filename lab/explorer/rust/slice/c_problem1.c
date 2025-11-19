#include <stdio.h>

int main()
{
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
	size_t len = sizeof arr / sizeof arr[0];
	for(int i = 0; i < len; i++)
	{
		printf("a[%i] = %i\n", i, arr[i]); 
	}

	int *p = &arr[5];
	int *q = p + 3;

	printf("p points to value: %d\n", *p);
	printf("q points to value: %d\n", *q);

	return 0;
}
