/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:16 by marvin            #+#    #+#             */
/*   Updated: 2025/06/12 22:03:22 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *new)
{
	int		i;
	char	*key;

	key = NULL;
	i = 0;
	while (new[i] && new[i] != '=')
		i++;
	key = ft_calloc(i + 1, sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, new, i + 1);
	return (key);
}

int	is_append(char *envp, char *key, char *new)
{
	int	len;

	len = ft_strlen(key);
	return (ft_strncmp(envp, key, len - 1) == 0 && envp[len - 1] == '='
		&& new[len] == '=' && new[len - 1] == '+');
}

int	is_replace(char *envp, char *key, char *new)
{
	int	len;

	len = ft_strlen(key);
	return (ft_strncmp(envp, key, len) == 0 && envp[len] == '='
		&& new[len] == '=');
}

int	ft_append(char *new, char *key, char *cpy)
{
	char	*tmp;
	char	*join;
	int		len;

	len = ft_strlen(key);
	tmp = cpy;
	join = ft_strjoin(cpy, new + len + 1);
	if (!join)
	{
		free(cpy);
		cpy = NULL;
		return (-1);
	}
	cpy = join;
	free(tmp);
	return (1);
}

int	ft_replace(char *new, char **cpy, int a)
{
	free(cpy[a]);
	cpy[a] = ft_strdup(new);
	if (!cpy[a])
		return (-1);
	return (1);
}