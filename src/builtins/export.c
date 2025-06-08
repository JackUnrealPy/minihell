/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:57:31 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/08 16:50:40 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_var(char *var_to_print)
{
	int	i;
	int	start_quote;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	start_quote = 1;
	while (var_to_print[i])
	{
		ft_putchar_fd(var_to_print[i], 1);
		if (var_to_print[i] == '=' && start_quote)
		{
			ft_putchar_fd('"', 1);
			start_quote = 0;
		}
		if (var_to_print[i + 1] == '\0' && !start_quote)
			ft_putchar_fd('"', 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

void	sort_export(char **envp)
{
	int		a;
	char	*old_smallest;
	char	*new_smallest;

	a = 0;
	old_smallest = NULL;
	while (1)
	{
		new_smallest = NULL;
		a = 0;
		while (envp[a])
		{
			if ((!new_smallest || (ft_strcmp(new_smallest, envp[a]) > 0))
				&& (!old_smallest || ft_strcmp(old_smallest, envp[a]) < 0)
				&& ((envp[a][0] >= 'A' && envp[a][0] <= 'Z')
					|| (envp[a][0] >= 'a' && envp[a][0] <= 'z')))
				new_smallest = envp[a];
			a++;
		}
		if (!new_smallest)
			break ;
		print_var(new_smallest);
		old_smallest = new_smallest;
	}
}

void	add_to_arr(t_hell *hell, t_proc *head)
{
	int	i;

	i = 1;
	while (head->cmd[i])
		i++;
	hell->envp = (char **)ft_mallocarr(hell, hell->freeme,
			(void **)ft_realloc_envp(hell->envp, i - 1, head->cmd + 1));
}

int	add_envp_var(t_hell *hell, t_proc *head)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (head->cmd && head->cmd[0] && !head->cmd[1])
		return (0);
	if (head->cmd[1][0] == 0 || (head->cmd[1][0] != '_'
			&& !ft_isalpha(head->cmd[1][0])))
		error = 1;
	while (head->cmd[1][0] != 0 && head->cmd[1][i] && head->cmd[1][i] != '=')
	{
		if (head->cmd[1][i] == '+' && head->cmd[1][i + 1] && head->cmd[1][i
			+ 1] == '=')
			;
		else if (!ft_isalnum(head->cmd[1][i]) && head->cmd[1][i] != '_')
			error = 1;
		i++;
	}
	if (error)
		return (built_err(hell, "export: `", "': not a valid identifier", 1));
	add_to_arr(hell, head);
	return (1);
}

void	ft_export(t_hell *hell, t_proc *head)
{
	if (add_envp_var(hell, head) || hell->exec_error)
		return ;
	if (head->cmd && head->cmd[0] && !head->cmd[1])
		sort_export(hell->envp);
}
