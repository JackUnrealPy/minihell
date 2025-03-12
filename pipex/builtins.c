#include "pipex_bonus.h"
#include <linux/limits.h>

void	ft_echo(char **args, int newline)
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
}
char	**ft_double_strdup(char **args, int i)
{
	int		a;
	int		b;
	char	**cpy;

	a = 0;
	while (args[a])
		a++;
	b = a;
	cpy = ft_calloc((a - i) + 1, sizeof(char *));
	a = 0;
	while (a < b - i)
	{
		cpy[a] = ft_strdup(args[a + i]);
		a++;
	}
	cpy[a] = NULL;
	return (cpy);
}

void	echo_init(char *argv[])
{
    char **args;
    int i = 2;
    if (strcmp("-n", argv[2]) == 0)
        i = 3;
	args = ft_double_strdup(argv, i);
	ft_echo(args, i);
}

void pwd_init(char **argv)
{
    char buf[PATH_MAX];

    getcwd(buf, sizeof(buf));
    printf("%s\n", buf);
}

void cd_init(char **argv)
{
    if (chdir("/bin") != 0)
        exit(errno);
}

void determine_builtin(char *argv[])
{
	if (strcmp("echo", argv[1]) == 0)
        echo_init(argv);
    if (strcmp("pwd", argv[1]) == 0)
        pwd_init(argv);
    if (strcmp("cd", argv[1]) == 0)
        cd_init(argv);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	determine_builtin(argv);
}