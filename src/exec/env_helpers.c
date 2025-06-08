/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:16 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 16:51:23 by nrumpfhu         ###   ########.fr       */
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
	ft_strlcpy(key, new, i + 1);
	return (key);
}

int	is_append(char *envp, char *key, char *new, int len)
{
	return (ft_strncmp(envp, key, len - 1) == 0 && envp[len - 1] == '='
		&& new[len] == '=' && new[len - 1] == '+');
}

int	is_replace(char *envp, char *key, char *new, int len)
{
	return (ft_strncmp(envp, key, len) == 0 && envp[len] == '='
		&& new[len] == '=');
}
