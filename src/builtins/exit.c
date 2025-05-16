/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:59:12 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/04/18 21:27:08 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	string_is_digit(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+' || (str[i] - 48 >= 0 && str[i]
			- 48 <= 9))
		i++;
	while (str[i])
	{
		if (!(str[i] - 48 >= 0 && str[i] - 48 <= 9))
			return (0);
		i++;
	}
	return (1);
}

int	error_check(const char *str)
{
	long	i;
	int		a;

	i = 0;
	while ((str[i] < 14 && str[i] > 8) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	while (str[i] == '0')
		i++;
	a = 0;
	while (str[i + a])
	{
		if (!string_is_digit(str + 1))
			return (1);
		a++;
	}
	if (a > 19)
		return (2);
	if (a == 19)
	{
		if (ft_strncmp(str + i, "9223372036854775807", 19) > 0)
		{
			if (str[0] == '-' && ft_strncmp(str + i, "9223372036854775808",
					19) <= 0)
				return (0);
			return (2);
		}
	}
	return (0);
}
long	ft_atol(const char *str)
{
	long	res;
	long	i;
	long	negative;

	negative = 1;
	res = 0;
	i = 0;
	while ((str[i] < 14 && str[i] > 8) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * negative);
}

void	free_exit(t_hell *hell, int error)
{
	close_proc(hell);
	rl_clear_history();
	throw_garbage(hell->freeme);
	free(hell->head);
	exit(error);
}

void	ft_exit(t_hell *hell, t_proc *head, int is_pipe)
{
	long	num;
	int		i;

	num = 0;
	i = 1;
	if (is_pipe)
	{
		return ;
	}
	if (head->cmd[0] && !head->cmd[1])
		free_exit(hell, 0);
	if (head->cmd[0])
	{
		if (string_is_digit(head->cmd[1]) && head->cmd[2])
			return (error_msg(hell, NULL, "exit: too many arguments", 1));
		if (!string_is_digit(head->cmd[i]) || ft_strncmp(head->cmd[i], "\0",
				ft_strlen(head->cmd[i])) == 0)
		{
			ft_putstr_fd("exit: ", 2);
			error_msg(hell, head->cmd[1], ": numeric argument required", 2);
			free_exit(hell, 2);
		}
		if (error_check(head->cmd[1]))
		{
			ft_putstr_fd("exit: ", 2), error_msg(hell, head->cmd[1],
				": numeric argument required", 2);
			free_exit(hell, 2);
		}
		num = ft_atol(head->cmd[i]);
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
		free_exit(hell, 0);
	}
}
