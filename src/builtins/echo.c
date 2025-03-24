#include "../../includes/minishell.h"

// void	ft_freedata(char **arr)
// {
// 	int	a;

// 	a = 0;
// 	if (!arr)
// 		return ;
// 	while (arr[a])
// 		a++;
// 	while (a >= 0)
// 	{
// 		free(arr[a]);
// 		a--;
// 	}
// 	free(arr);
// 	arr = NULL;
// }

void	print_echo(char **args, int newline, t_proc *lst)
{
	int	i;
	int fd = 1;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd); // change fd
		if (args[i] && args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (newline == 1)
		ft_putchar_fd('\n', fd);
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

void	ft_echo(t_hell *hell)
{
	int i = 1;
	if (strcmp("-n", (*hell->head)->cmd[1]) == 0) // forbidden function
		i = 2;
	print_echo((*hell->head)->cmd+i, i, *(hell->head));
	// where are args saved?
}