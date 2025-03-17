#include "builtins.h"

void	print_echo(char **args, int newline)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (newline == 2)
		ft_putchar('\n');
	ft_freedata(args);
}

char	**ft_double_strdup(char **args)
{
	int		a;
	int		b;
	char	**cpy;

	a = 0;
	while (args[a])
		a++;
	b = a;
	cpy = ft_calloc(a + 1, sizeof(char *));
	a = 0;
	while (a < b)
	{
		cpy[a] = ft_strdup(args[a]);
		a++;
	}
	cpy[a] = NULL;
	return (cpy);
}

void	ft_echo(char *argv[])
{
	char **args;
	int i = 2;
	if (strcmp("-n", argv[2]) == 0)
		i = 3;
	args = ft_double_strdup(argv + i);
	print_echo(args, i);
}