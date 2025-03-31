/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/03/28 17:53:44 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	ft_expand(t_hell *hell, t_proc *proc, char *str)
{
	int		i;
	char	*token;
	int		j;
	int		k;
	char	*s;

	if (str[1] == '?')
	{
		s = ft_malloc(hell, proc->freeme, ft_itoa(hell->lastexit));
		add_to_cmdarr(hell, proc, s);

		return (ft_strlen(s));
	}
	i = 0;
	while (str[++i])
	{
		if(ft_isspace(str[i]) || ismeta(str + i))
			break;	
	}
	j = -1;
	while (hell->envp[++j])
	{
		if (!ft_strncmp(str + 1, hell->envp[j], i - 1) && hell->envp[j][i - 1] == '=')
		{
			k = -1;
			while(hell->envp[j][i + ++k])
			{
				if (ft_isspace(hell->envp[j][i + k]))
					continue ;
				else if (hell->envp[j][i + k] == '$')
					k += ft_expand(hell, proc, hell->envp[j] + i + k);
				else if (hell->envp[j][i + k] == '\'')
					k += get_squote(hell, proc, hell->envp[j] + i + k);
				else
					k += get_cmdarr(hell, hell->envp[j] + i + k, proc);
			}
			return (i - 1);
		}
	}		
	return (i);

}