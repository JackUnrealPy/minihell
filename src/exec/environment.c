/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:19 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 18:14:34 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *key, char **envp, int print_key)
{
	char	*value;
	int		i;
	int		a;
	int		len;

	value = NULL;
	i = 0;
	a = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
			a = 1;
			while (envp[i] && envp[i][a + len] && envp[i][a + len] != '\n')
				a++;
			if (envp[i] && !print_key)
				value = ft_substr(envp[i], len + 1, a - 1);
			else if (envp[i] && print_key)
				value = ft_strdup(envp[i]);
		}
		i++;
	}
	return (value);
}

char	**ft_double_strdup(t_hell *hell, char **envp)
{
	int		a;
	int		b;
	char	**my_env;

	a = 0;
	while (envp[a])
		a++;
	b = a;
	my_env = ft_calloc((a + 1) * sizeof(char *), sizeof(char *));
	if (!my_env)
		init_mem(hell, NULL, NULL, NULL);
	a = 0;
	while (a < b)
	{
		if (a == b - 1)
			my_env[a] = ft_strdup("_=/bin/env");
		else
			my_env[a] = ft_strdup(envp[a]);
		if (!my_env[a])
			(ft_freeme(my_env), init_mem(hell, NULL, NULL, NULL));
		a++;
	}
	return (my_env);
}

void	fill_env_cpy(char **cpy, char *new, char *key, int found)
{
	int		len;
	int		a;
	char	*tmp;

	len = ft_strlen(key);
	a = -1;
	while (cpy[++a] && !found)
	{
		if (is_append(cpy[a], key, new, len))
		{
			tmp = cpy[a];
			cpy[a] = ft_strjoin(cpy[a], new + len + 1);
			free(tmp);
			found = 1;
		}
		if (is_replace(cpy[a], key, new, len))
		{
			free(cpy[a]);
			cpy[a] = ft_strdup(new);
			found = 1;
		}
	}
	if (!found)
		cpy[a] = ft_strdup(new);
}

char	**ft_realloc_envp(char **envp, int new_element, char **new)
{
	int		a;
	char	**cpy;
	char	*key;
	int		i;

	i = 0;
	a = 0;
	while (envp[a])
		a++;
	cpy = ft_calloc(a + new_element + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	a = -1;
	while (envp[++a])
		cpy[a] = ft_strdup(envp[a]);
	while (new[i])
	{
		key = get_key(new[i]);
		if (!key)
			return (NULL);
		fill_env_cpy(cpy, new[i], key, 0);
		free(key);
		i++;
	}
	return (cpy);
}
