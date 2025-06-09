#include "../../includes/minishell.h"

static char	*lookup_exp_val(t_hell *hell, t_proc *proc, char *str)
{
	char	*res;
	int		i;

	res = NULL;
	i = -1;
	while (hell->envp[++i])
	{
		if (!ft_strncmp(hell->envp[i], str, ft_strlen(str))
			&& hell->envp[i][ft_strlen(str)] == '=')
			res = ft_malloc(hell, proc->freeme,
					ft_substr(hell->envp[i], ft_strlen(str) + 1,
						ft_strlen(hell->envp[i]) - ft_strlen(str)));
	}
	return (res);
}

static char	*expand_exit(t_hell *hell, t_proc *proc)
{
	char	*var;

	var = NULL;
	var = ft_malloc(hell, proc->freeme, ft_itoa(hell->lastexit));
	return (var);
}

char	*get_var(t_hell *hell, t_proc *proc, char *str, int *i)
{
	char	*s;
	char	*var;

	var = NULL;
	while (++*i)
	{
		if (!str[*i] || !ft_isalnum(str[*i]))
		{
			s = ft_malloc(hell, proc->freeme, ft_substr(str, 1, *i - 1));
			var = lookup_exp_val(hell, proc, s);
			break ;
		}
	}
	return (var);
}

char	*get_exp(t_hell *hell, t_proc *proc, char *str, int *i)
{
	char	*var;

	var = NULL;
	*i = 0;
	if (str[1] == '?')
	{
		var = expand_exit(hell, proc);
		*i = 2;
	}
	else
		var = get_var(hell, proc, str, i);
	if (*i == 1 && *str == '$')
		var = ft_malloc(hell, proc->freeme, ft_strdup("$"));
	if (!var)
		var = ft_malloc(hell, proc->freeme, ft_strdup(""));
	return (var);
}
