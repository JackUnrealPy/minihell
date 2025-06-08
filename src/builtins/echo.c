/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:58 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 15:35:54 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_from(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
	{
		if (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			n = 1;
			while (cmd[i][n])
			{
				if (cmd[i][n] && cmd[i][n] != 'n')
					return (i);
				n++;
			}
		}
		i++;
	}
	return (i);
}

int	print_newline(char **cmd)
{
	int	n;

	if (!cmd[1] || (cmd[1] && ft_strncmp(cmd[1], "-n", 2) != 0))
		return (1);
	n = 1;
	while (cmd[1][n])
	{
		if (cmd[1][n] && cmd[1][n] != 'n')
			return (1);
		n++;
	}
	return (0);
}

void	ft_echo(t_proc *head)
{
	int	i;

	i = print_from(head->cmd);
	while (head->cmd[i])
	{
		ft_putstr_fd(head->cmd[i], 1);
		if (head->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (print_newline(head->cmd))
		ft_putchar_fd('\n', 1);
}
