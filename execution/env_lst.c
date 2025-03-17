#include "execution.h"

t_list *create_env_list(char **envp)
{
	int i = 1;
	t_list *env_lst = ft_lstnew(envp[0]);
	while (envp[i])
	{
		ft_lstadd_back(&env_lst, ft_lstnew(envp[i]));
		i++;
	}
	return (env_lst);
}

void print_list(t_list *a)
{
	while (a->next)
	{
		printf("%s\n", (char *)a->content);
		a = a->next;
	}
}