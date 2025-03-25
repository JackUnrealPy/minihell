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

void ft_unset(char **envp, char *var_to_delete)
{
	int i = 0;
	int strcount = 0;
	while (envp[strcount])
		strcount++;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_to_delete, ft_strlen(var_to_delete)) == 0)
		{
			free(envp[i]);
			while (envp[i])
			{
				envp[i] = envp[i+1];
				i++;
			}
			envp[i] = NULL;
			break;
		}
		i++;
	}
}