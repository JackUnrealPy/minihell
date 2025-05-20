/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:18:19 by marvin            #+#    #+#             */
/*   Updated: 2025/05/20 04:19:41 by marvin           ###   ########.fr       */
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
	len = strlen(key);
	while (envp[i])
	{
		if (strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
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
	my_env = malloc((a + 1) * sizeof(char *));
	if (!my_env)
		return (error_msg(hell, NULL, "Memory allocation failed", 1), NULL);
	a = 0;
	while (a < b)
	{
		my_env[a] = ft_strdup(envp[a]);
		if (!my_env[a])
		{
			error_msg(hell, NULL, "Memory allocation failed", 1);
			return (ft_freeme(my_env), NULL);
		}
		a++;
	}
	my_env[a] = NULL;
	return (my_env);
}

void	fill_env_cpy(char **envp, char **cpy, char *new, char *key)
{
	int	len;
	int	found;
	int	a;

	len = ft_strlen(key);
	found = 0;
	a = -1;
	while (envp[++a])
	{
		if (!found && is_append(envp[a], key, new, len))
		{
			cpy[a] = ft_strjoin(envp[a], new + len + 1);
			found = 1;
		}
		else if (!found && is_replace(envp[a], key, new, len))
		{
			cpy[a] = ft_strdup(new);
			found = 1;
		}
		else
			cpy[a] = ft_strdup(envp[a]);
	}
	if (!found)
		cpy[a] = ft_strdup(new);
	cpy[a + 1] = NULL;
}

char	**ft_realloc_envp(t_hell *hell, char **envp, int new_element, char *new)
{
	int		a;
	char	**cpy;
	char	*key;

	(void)hell;
	a = 0;
	while (envp[a])
		a++;
	cpy = ft_calloc(a + new_element + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	key = get_key(new);
	if (!key)
		return (NULL);
	fill_env_cpy(envp, cpy, new, key);
	free(key);
	return (cpy);
}
