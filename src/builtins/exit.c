#include "../../includes/minishell.h"

int		string_is_digit(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '-' || (str[i] - 48 >= 0 && str[i] - 48 <= 9))
			i++;
		else
			return(0);
	}
	return (1);
}

void	ft_exit(t_hell *hell, t_proc *head, char **cmd, int is_pipe)
{
	// change SHLVL
	int num;
	if (head->cmd[0] && head->cmd[1] && head->cmd[2])
	{
		error_msg(hell, "exit: too many arguments", -1);
		hell->lastexit = 1;
		return ;
	}
	else if (head->cmd[0] && head->cmd[1])
	{
		num = ft_atoi(head->cmd[1]);
		if (num < 0)
		{
			while (num * -1 > 256)
				num += 256;
		}
		if (!string_is_digit(head->cmd[1]))
		{
			(ft_putstr_fd("exit: ", 2), ft_putstr_fd(head->cmd[1], 2), ft_putendl_fd(": numeric argument required", 2));
			num = 2;
		}
	}
	else
		num = 0;
	hell->lastexit = num;
	if (!is_pipe)
	{
		ft_putendl_fd("exit", 1);
		ft_terminate(1, cmd);
		jump_ship(hell, num);
	}
}