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

void	unset_errors(t_hell *hell, char *var_to_delete)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if ((var_to_delete[0] != '_' && !ft_isalpha(var_to_delete[0])))
		error = 1;
	while (var_to_delete[i] && var_to_delete[i] != '=')
	{
		if (!ft_isalnum(var_to_delete[i]) && var_to_delete[i] != '_' && var_to_delete[i] != '=')
			error = 1;
		i++;
	}
	// if (error)
	// {
	// 	ft_putstr_fd("unset: `", 2);
	// 	ft_putstr_fd(var_to_delete, 2);
	// 	error_msg(hell, NULL, "': not a valid identifier", 1);
	// }
	(void)hell;
}

void ft_unset(t_hell *hell, char **envp, char *var_to_delete)
{
	if (!var_to_delete)
		return ;
	//unset_errors(hell, var_to_delete);
	if (hell->exec_error)
		return ;
	int i = 0;
	int strcount = 0;
	while (envp[strcount])
		strcount++;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_to_delete, ft_strlen(var_to_delete)) == 0)
		{
			//free(envp[i]);
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
	//sort_export(envp);

}