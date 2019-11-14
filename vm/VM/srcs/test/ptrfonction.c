#include <stdio.h>

typedef void	(*callback)(int, char *s);

void		oui(int nb, char *s)
{
	printf("Vous avez attendu %d tours\n, felicitation %s\n", nb, s);
}

callback	test(char **s, int num)
{
	printf("initialisation dans test\n");
	*s = strdup("bonjour niakwe");
	num = 0;
	return (oui);
}

int		main()
{
	int		nb;
	char	*s;
	callback	cb;

	s = NULL;
	nb = 0;
	while (nb < 5)
	{
		if (nb == 0)
			cb = test(&s, nb);
		else if (nb == 4)
			cb(nb + 1, s);
		nb++;
		printf("tour++\n");
	}
}
