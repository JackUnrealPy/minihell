#include "../../includes/minishell.h"

int		string_is_digit(char *str)
{
	int i = 0;
	if (str[i] == '-' || str[i] == '+' || (str[i] - 48 >= 0 && str[i] - 48 <= 9))
		i++;
	while (str[i])
	{
		if (!(str[i] - 48 >= 0 && str[i] - 48 <= 9))
			return(0);
		i++;
	}
	return (1);
}

void	ft_exit(t_hell *hell, t_proc *head, char **cmd, int is_pipe)
{
	// change SHLVL
	int num = 0;
	int i = 1;
	if (head->cmd[0])
	{
		while (head->cmd[i])
		{
			num = ft_atoi(head->cmd[i]); // custom atoi: jump over any zero directly after +/-, compare with atol, count length (after zeros etc)
			//printf("num: %i", num);
			if (i > 1 && head->cmd[i])
			{
				error_msg(hell, cmd, "exit: too many arguments", 1);
				return ;
			}
			if (!string_is_digit(head->cmd[i]) || ft_strncmp(head->cmd[i], "\0", ft_strlen(head->cmd[i])) == 0)
			{
				(ft_putstr_fd("exit: ", 2), ft_putstr_fd(head->cmd[1], 2), ft_putendl_fd(": numeric argument required", 2));
				error_msg(hell, cmd, NULL, 2);
				return ;
			}
			i++;
		}
	}
	if (head->cmd[0] && head->cmd[1])
	{
		num = ft_atoi(head->cmd[1]);
		if (num < 0)
		{
			while (num * -1 > 256)
				num += 256;
		}
	}
	hell->lastexit = num;
	if (!is_pipe)
	{
		ft_putendl_fd("exit", 1);
		if (cmd)
			ft_terminate(1, cmd);
		jump_ship(hell, num);
	}
}
