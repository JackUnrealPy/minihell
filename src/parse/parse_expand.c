/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/05/13 21:53:26 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*ft_getvar(t_hell *hell, t_proc *proc, char *str)
{
	char	*res;
	int		i;

	res = NULL;	
	i = -1;
	while(hell->envp[++i])
	{
		if (!ft_strncmp(hell->envp[i], str, ft_strlen(str)) && hell->envp[i][ft_strlen(str)] == '=')
			res = ft_malloc(hell, proc->freeme, ft_substr(hell->envp[i], ft_strlen(str) + 1, ft_strlen(hell->envp[i]) - ft_strlen(str)));
	}

	return (res);
}

static char	*expand_exit(t_hell *hell, t_proc *proc)
{
	char	*var;

		var = NULL;
		var = ft_malloc(hell, proc->freeme, ft_itoa(hell->lastexit));
	return	(var);
}


int	ft_expand(t_hell *hell, t_proc *proc, char **str, int pos)
{
	int		i;
	char	*s;
	char	*res;
	char	*var;

	i = 0;
	var = NULL;
	if ((*str)[pos + 1] == '?')
	{
		var = expand_exit(hell, proc);
		i = 2;
	}
	else
	{
		while (++i)
		{
			if(!(*((*str) + pos + i)) || ft_isspace(*((*str) + pos + i)) || ismeta((*str) + pos + i))
			{
				s = ft_malloc(hell, proc->freeme, ft_substr(*str, pos + 1, i - 1));
				var = ft_getvar(hell, proc, s);
				if (!var)
					var = getenv(s);
				break;	
			}
		}
	}
	if (i == 1 && *((*str) + pos) == '$')
		var = "$";	
	if (!var)
		var = "";
	res = ft_malloc(hell, proc->freeme, ft_calloc(sizeof(char), (ft_strlen(*str) - (i - 1) + ft_strlen(var) + 1)));
	ft_memcpy(res, *str, pos);
	ft_memcpy(res + pos, var, ft_strlen(var) + 1);
	ft_memcpy(res + pos + ft_strlen(var), (*str + pos) + i , ft_strlen(*str) - (pos + i));
	*str = res;
	proc->var = ft_strlen(var);
	return (ft_strlen(var));
}