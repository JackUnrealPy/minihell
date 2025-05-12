#include "../../includes/minishell.h"

char	*ft_getenv(char *key, char **envp)
{
	char *value = NULL;
	int i = 0;
	int a = 0;
    int len = strlen(key);
	while (envp[i])
	{
		if (strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
            a = 1;
            while (envp[i] && envp[i][a+len] && envp[i][a+len] != '\n')
                a++;
            value = ft_substr(envp[i], len + 1, a - 1);
		}
        i++;
	}
	return(value);
}

char	**ft_double_strdup(t_hell *hell, char **envp, char **cmd)
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
		error_msg(hell, cmd, "Memory allocation failed", 1);
		return (NULL);
	}
	a = 0;
	while (a < b)
	{
		my_env[a] = ft_strdup(envp[a]);
		if (!my_env[a])
		{
			error_msg(hell, cmd, "Memory allocation failed", 1);
			ft_freeme(my_env);
			return (NULL);
		}
		a++;
	}
	my_env[a] = NULL;
	return (my_env);
}

char	**ft_realloc_envp(char **envp, int new_element, char *new)
{
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
	int ik=0;
	while (new[ik] && new[ik] != '=')
	{
		ik++;
	}
	char key[ik+1];
	ft_strlcpy(key, new, ik+1);
	int len = ft_strlen(key);
	// printf("key: [%s]\n", key);
	// printf("diff: {%d}\n", ft_strncmp("zz=h\n", key, ft_strlen(key)));
	int found = 0;
	while (envp[a] && a < b)
	{
		if (ft_strncmp(envp[a], key, ft_strlen(key)) == 0 && envp[a][len] == '=' && new[len] == '=')
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

// // void add_list_element(t_list *a, void *content)
// // {
// // 	while (a->next)
// // 		a = a->next;
// // 	a->content = ft_lstnew(content);
// // 	a->next = NULL;
// // }

// // t_list *create_env_list(char **envp)
// // {
// // 	int i = 1;
// // 	t_list *env_lst = ft_lstnew(envp[0]);
// // 	while (envp[i])
// // 	{
// // 		ft_lstadd_back(&env_lst, ft_lstnew(envp[i]));
// // 		i++;
// // 	}
// // 	return (env_lst);
// // }

// // void print_list(t_list *a)
// // {
// // 	while (a->next)
// // 	{
// // 		printf("%s\n", (char *)a->content);
// // 		a = a->next;
// // 	}
// // }
