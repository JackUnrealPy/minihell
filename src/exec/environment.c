#include "../../includes/minishell.h"

void	ft_double_strdup(t_hell *hell, char **envp)
{
	int		a;
	int		b;

	a = 0;
	while (envp[a])
		a++;
	b = a;
	hell->envp = ft_calloc(a + 1, sizeof(char *));
	a = 0;
	while (a < b)
	{
		hell->envp[a] = ft_strdup(envp[a]);
		a++;
	}
	hell->envp[a] = NULL;
}

// char	**ft_realloc_envp(char **envp, int new_element, char *new)
// {
// 	int		a;
// 	int		b;
// 	char	**cpy;

// 	a = 0;
// 	while (args[a])
// 		a++;
// 	b = a + new_element;
// 	cpy = ft_calloc(a + new_element + 1, sizeof(char *));
// 	if (!cpy)
// 		return(NULL);
// 	a = 0;
// 	while (a < b)
// 	{
// 		if ((a == b - 1) && new_element)
// 			cpy[a] = ft_strdup(new); // add protection
// 		else
// 			cpy[a] = ft_strdup(args[a]); // add protection
// 		a++;
// 	}
// 	cpy[a] = NULL;
// 	ft_freedata(args);
// 	return (cpy);
// }

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

void print_list(t_proc *a)
{
	t_redir	*reds;
	int		i;

	while (a)
	{
		if (a->cmd && *(a->cmd))
		{
			i = -1;
			while (a->cmd[++i])
				printf("cmd [%d]:{%s}\n", i, a->cmd[i]);
		}
		reds = *(a->redirs);
		while (reds)
		{
			printf("reds [%d]:{%s}\n", reds->type, reds->pathordel);
			reds = reds->next;
		}	
		a = a->next;
	}
}
