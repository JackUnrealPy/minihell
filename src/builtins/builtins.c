/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:49 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 16:49:04 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_err(t_hell *hell, char *type, char *msg, int exitnum)
{
	ft_putstr_fd(type, 2);
	error_msg(hell, (*hell->head)->cmd[1], msg, exitnum);
	if (exitnum == 2)
		jump_ship(hell, exitnum);
	return (0);
}

// void	error_msg(t_hell *hell, char *var, char *error, int exitcode)
// {
// 	if (error)
// 	{
// 		if (var)
// 			ft_putstr_fd(var, STDERR_FILENO);
// 		ft_putendl_fd(error, STDERR_FILENO);
// 	}
// 	hell->lastexit = exitcode;
// 	hell->exec_error = 1;
// 	if (hell->cmd_count > 1)
// 		ft_close(hell);
// }

int	is_builtin(t_proc *head)
{
	if (!head->cmd)
		return (0);
	else if (ft_strcmp(head->cmd[0], "echo") | ft_strcmp(head->cmd[0],
			"pwd") | ft_strcmp(head->cmd[0], "cd") | ft_strcmp(head->cmd[0],
			"env") | ft_strcmp(head->cmd[0], "export") | ft_strcmp(head->cmd[0],
			"unset") | ft_strcmp(head->cmd[0], "exit"))
		return (1);
	else
		return (0);
}

int	determine_builtin(t_hell *hell, t_proc *head, int pipe)
{
	if (!head->cmd || !head->cmd[0])
		return (0);
	else if (ft_strncmp(head->cmd[0], "echo", ft_strlen(head->cmd[0])) == 0)
		ft_echo(head);
	else if (ft_strcmp("pwd", head->cmd[0]) == 0)
		ft_pwd(hell, *(head->redirs), pipe);
	else if (ft_strcmp("cd", head->cmd[0]) == 0)
		ft_cd(hell, head);
	else if (ft_strcmp("env", head->cmd[0]) == 0)
		ft_env((*head->redirs), hell->envp, pipe);
	else if (ft_strcmp("export", head->cmd[0]) == 0)
		ft_export(hell, head);
	else if (ft_strncmp("unset", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
		ft_unset(hell, hell->envp, head->cmd);
	else if (ft_strncmp("exit", head->cmd[0], ft_strlen(head->cmd[0])) == 0)
		ft_exit(hell, head, pipe);
	else
		return (0);
	if (!hell->exec_error)
		hell->lastexit = 0;
	return (1);
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
