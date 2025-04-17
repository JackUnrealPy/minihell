#include "../../includes/minishell.h"

void	print_export(char **envp);
void	sort_export(char **envp);

void ft_unset(char **envp, char *var_to_delete)
{
	if (!var_to_delete)
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