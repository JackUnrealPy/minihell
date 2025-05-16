#include "../../includes/minishell.h"

void	ft_unset(t_hell *hell, char **envp, char *var_to_delete)
{
	if (!var_to_delete)
		return ;
	// unset_errors(hell, var_to_delete);
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
			// free(envp[i]);
			while (envp[i])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			break ;
		}
		i++;
	}
	// sort_export(envp);
}