#include <string.h>
#include <stdio.h>

int		main(void)
{
	int		a = 5;
	int		b;

	memcpy(&b, &a, 4);
	printf("a = %d, b = %d\n", a, b);
	return (0);
}

