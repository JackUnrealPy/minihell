#include "../../includes/minishell.h"

// void ft_unset(char **envp, char *var_to_delete)
// {
// 	t_list *env_lst = create_env_list(envp);
// 	while (env_lst)
// 	{
// 		if (ft_strncmp((char *)env_lst, var_to_delete, ft_strlen(var_to_delete)))
// 		{
// 			ft_lstdelone(env_lst, del);
// 			return ;
// 		}
// 		env_lst = env_lst->next;
// 	}
// 	print_list(env_lst);
// }

void ft_unset(char **my_envp, char *var_to_delete)
{
	int i = 0;
	int strcount = 0;
	while (my_envp[strcount])
		strcount++;
	while (my_envp[i])
	{
		if (ft_strncmp(my_envp[i], var_to_delete, ft_strlen(var_to_delete)) == 0)
		{
			free(my_envp[i]);
			while (my_envp[i])
			{
				my_envp[i] = my_envp[i+1];
				i++;
			}
			my_envp[i] = NULL;
			break;
		}
		i++;
	}
}