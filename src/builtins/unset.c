/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:19:19 by marvin            #+#    #+#             */
/*   Updated: 2025/06/07 19:50:10 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_hell *hell, char **envp, char **var_to_delete)
{
	int	i;
	int	num = 1;

	if (!var_to_delete)
		return ;
	if (hell->exec_error)
		return ;
	i = 0;
	while (var_to_delete[num])
	{
		i = 0;
		while (envp[i])
		{
			if (ft_strncmp(envp[i], var_to_delete[num], ft_strlen(var_to_delete[num])) == 0)
			{
				while (envp[i])
				{
					envp[i] = envp[i + 1];
					i++;
				}
				envp[i] = NULL;
				break ;
			}
			i++;
		}
		num++;
	}
}
