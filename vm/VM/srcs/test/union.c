#include <stdlib.h>
#include <string.h>

int		main(int ac, char *av[])
{
	int		nb = atoi(av[1]);
	int		a;

	a = 0;
	memcpy(&a, &nb, 1);
	printf("int = %d\n", a);
	printf("short = %d\n", a);
	printf("char = %d\n", a);
	return (0);
	
}
