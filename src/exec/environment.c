#include "../../includes/minishell.h"

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
	while (a < b)
	{
		if ((a == b - 1) && new_element)
			cpy[a] = ft_strdup(new); // add protection
		else
			cpy[a] = ft_strdup(envp[a]); // add protection
		a++;
	}
	cpy[a] = NULL;
	//ft_freedata(envp);
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
