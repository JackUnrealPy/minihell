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
	{
		error_msg(hell, NULL, "Memory allocation failed", 1);
		return (NULL);
	}
	a = 0;
	while (a < b)
	{
		my_env[a] = ft_strdup(envp[a]);
		if (!my_env[a])
		{
			error_msg(hell, NULL, "Memory allocation failed", 1);
			ft_freeme(my_env);
			return (NULL);
		}
		a++;
	}
	my_env[a] = NULL;
	return (my_env);
}

char	**ft_realloc_envp(t_hell *hell, char **envp, int new_element, char *new)
{
	(void)hell;
	int		a;
	int		b;
	char	**cpy;

	a = 0;
	while (envp[a])
		a++;
	b = a + new_element;
	cpy = ft_calloc(a + new_element + 1, sizeof(char *));
	if (!cpy)
		return(NULL);
	a = 0;
	int i=0;
	while (new[i] && new[i] != '=')
		i++;
	char key[i+1];
	ft_strlcpy(key, new, i+1);
	int len = ft_strlen(key);
	int found = 0;
	while (envp[a] && a < b)
	{
		if (ft_strncmp(envp[a], key, i-1) == 0 && envp[a][len-1] == '=' && new[len] == '=' && new[len-1] == '+')
		{
			cpy[a] = ft_strjoin(envp[a], new+i+1);
			found = 1;
		}
		else if (!found && ft_strncmp(envp[a], key, ft_strlen(key)) == 0 && envp[a][len] == '=' && new[len] == '=')
		{
			cpy[a] = ft_strdup(new);
			found = 1;
		}
		else
			cpy[a] = ft_strdup(envp[a]);
		a++;
	}
	if (!found)
		cpy[a] = ft_strdup(new);
	cpy[a+1] = NULL;
	return (cpy);
}


// #include "../../includes/minishell.h"

// char	*ft_getenv(char *key, char **envp, int print_key)
// {
// 	char	*value;
// 	int		i;
// 	int		a;
// 	int		len;

// 	value = NULL;
// 	i = 0;
// 	a = 0;
// 	len = strlen(key);
// 	while (envp[i])
// 	{
// 		if (strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
// 		{
// 			a = 1;
// 			while (envp[i] && envp[i][a + len] && envp[i][a + len] != '\n')
// 				a++;
// 			if (envp[i] && !print_key)
// 				value = ft_substr(envp[i], len + 1, a - 1);
// 			else if (envp[i] && print_key)
// 				value = ft_strdup(envp[i]);
// 		}
// 		i++;
// 	}
// 	return (value);
// }

// char	**ft_double_strdup(t_hell *hell, char **envp)
// {
// 	int		a;
// 	int		b;
// 	char	**my_env;

// 	a = 0;
// 	while (envp[a])
// 		a++;
// 	b = a;
// 	my_env = malloc((a + 1) * sizeof(char *));
// 	if (!my_env)
// 		return (error_msg(hell, NULL, "Memory allocation failed", 1), NULL);
// 	a = 0;
// 	while (a < b)
// 	{
// 		my_env[a] = ft_strdup(envp[a]);
// 		if (!my_env[a])
// 		{
// 			error_msg(hell, NULL, "Memory allocation failed", 1);
// 			return (ft_freeme(my_env), NULL);
// 		}
// 		a++;
// 	}
// 	my_env[a] = NULL;
// 	return (my_env);
// }

// int	ft_strlen_double(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr && arr[i])
// 		i++;
// 	return (i);
// }

// // int	realloc_loop(char **envp, char **cpy, char *key, char *new, int i,
// 		// int found, int a)
// // {

// // 	if (ft_strncmp(envp[a], key, i - 1) == 0 && envp[a][len - 1] == '='
// // 		&& new[len] == '=' && new[len - 1] == '+')
// // 	{
// // 		cpy[a] = ft_strjoin(envp[a], new + i + 1);
// // 		found = 1;
// // 	}
// // 	else if (!found && ft_strncmp(envp[a], key, ft_strlen(key)) == 0
// // 		&& envp[a][len] == '=' && new[len] == '=')
// // 	{
// // 		cpy[a] = ft_strdup(new);
// // 		found = 1;
// // 	}
// // 	else
// // 		cpy[a] = ft_strdup(envp[a]);
// // 	return (found);
// // }

// char	**ft_realloc_envp(t_hell *hell, char **envp, int new_element, char *new)
// {
// 	int		a;
// 	char	**cpy;
// 	int		i;
// 	int		found;
// 	char	*key;
// 	int		len;

// 	cpy = ft_calloc(ft_strlen_double(envp) + new_element + 1, sizeof(char *));
// 	if (!cpy)
// 		return (NULL);
// 	a = 0;
// 	i = 0;
// 	while (new[i] && new[i] != '=')
// 		i++;
// 	key = ft_calloc(i + 1, sizeof(char));
// 	ft_strlcpy(key, new, i + 1);
// 	found = 0;
// 	len = ft_strlen(key);
// 	// envp, new, i, key, cpy
// 	while (*envp)
// 	{
// 		if (ft_strncmp(*envp, key, i - 1) == 0 && *envp[len - 1] == '='
// 			&& new[len] == '=' && new[len - 1] == '+')
// 		{
// 			cpy[a] = ft_strjoin(*envp, new + i + 1);
// 			found = 1;
// 		}
// 		else if (!found && ft_strncmp(*envp, key, ft_strlen(key)) == 0
// 			&& *envp[len] == '=' && new[len] == '=')
// 		{
// 			cpy[a] = ft_strdup(new);
// 			found = 1;
// 		}
// 		else
// 			cpy[a] = ft_strdup(*envp);
// 		a++;
// 		envp++;
// 	}
// 	if (!found)
// 		cpy[a] = ft_strdup(new);
// 	free(key);
// 	return (cpy);
// 	(void)hell;
// }

// // // void add_list_element(t_list *a, void *content)
// // // {
// // // 	while (a->next)
// // // 		a = a->next;
// // // 	a->content = ft_lstnew(content);
// // // 	a->next = NULL;
// // // }

// // // t_list *create_env_list(char **envp)
// // // {
// // // 	int i = 1;
// // // 	t_list *env_lst = ft_lstnew(envp[0]);
// // // 	while (envp[i])
// // // 	{
// // // 		ft_lstadd_back(&env_lst, ft_lstnew(envp[i]));
// // // 		i++;
// // // 	}
// // // 	return (env_lst);
// // // }

// // // void print_list(t_list *a)
// // // {
// // // 	while (a->next)
// // // 	{
// // // 		printf("%s\n", (char *)a->content);
// // // 		a = a->next;
// // // 	}
// // // }