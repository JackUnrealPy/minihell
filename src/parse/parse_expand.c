/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:52:33 by agara             #+#    #+#             */
/*   Updated: 2025/04/22 19:05:14 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*ft_getvar(char *str)
{
	(void)str;
	return NULL;
}

static char	*expand_exit(t_hell *hell, t_proc *proc)
{
	char	*var;

		var = NULL;
		var = ft_malloc(hell, proc->freeme, ft_itoa(hell->lastexit));
	return	(var);
}


void	ft_expand(t_hell *hell, t_proc *proc, char **str, int pos)
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
				var = getenv(s);
				if (!var)
					var = ft_getvar(s);
				break;	
			}
		}
	}
	if (i == 1 && *((*str) + pos) == '$')
		var = "$";	
	if (!var)
		var = "";
	res = ft_malloc(hell, proc->freeme, malloc(sizeof(char) * (ft_strlen(*str) - (i - 1) + ft_strlen(var) + 1)));
	ft_memcpy(res, *str, pos);
	ft_memcpy(res + pos, var, ft_strlen(var) + 1);
	ft_memcpy(res + pos + ft_strlen(var), (*str + pos) + i , ft_strlen(*str) - (pos + i));
	res[ft_strlen(*str) + ft_strlen(var) - i] = 0;
	*str = res;
}