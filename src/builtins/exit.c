/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:59:12 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/12 13:57:49 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	string_is_digit(const char *str)
{
	int	i = 0;

	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i])
		return (0);
	return (1);
}


int	check_long(const char *str, int i, int a, int negative)
{
	// printf("comp: %d\n", ft_strncmp(str + i, "9223372036854775808",
	// 				19) > 0);
	if (a > 19)
		return (2);
	if (a == 19)
	{
		if (ft_strncmp(str + i, "9223372036854775807", 19) > 0)
		{
			if (i > 0 && negative && ft_strncmp(str + i, "9223372036854775808",
					19) <= 0)
				return (0);
			return (2);
		}
	}
	return (0);
}

int	error_check(const char *str)
{
	long	i;
	int		a;
	int sign = 0;

	i = 0;
	while ((str[i] < 14 && str[i] > 8) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	while (str[i] == '0')
		i++;
	a = 0;
	while (str[i + a])
	{
		if (!ft_isdigit(str[i+a]))
		{
			if ((a > 0 || str[i+a-1] == '0') && all_whitespace((char *)str+i+a))
				break;
			return (1);
		}
		a++;
	}
	return (check_long(str, i, a, sign));
}

int	exit_error(t_hell *hell, t_proc *head)
{
	if (string_is_digit(head->cmd[1]) && head->cmd[2])
		return (error_msg(hell, NULL, "exit: too many arguments", 1), 1);
	if (!string_is_digit(head->cmd[1]) || ft_strncmp(head->cmd[1], "\0",
			ft_strlen(head->cmd[1])) == 0)
		built_err(hell, "exit: ", ": numeric argument required", 2);
	if (error_check(head->cmd[1]))
		built_err(hell, "exit: ", ": numeric argument required", 2);
	return (0);
}

void	ft_exit(t_hell *hell, t_proc *head, int is_pipe)
{
	long	num;

	num = 0;
	if (is_pipe)
		return ;
	if (head->cmd[0] && !head->cmd[1])
		jump_ship(hell, 0);
	if (head->cmd[0])
	{
		if (exit_error(hell, head) == 1)
			return ;
	}
	num = ft_atol(head->cmd[1]);
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
	ft_putendl_fd("exit", 1);
	jump_ship(hell, hell->lastexit);
}
