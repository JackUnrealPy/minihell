#include "../../includes/minishell.h"
#include <linux/limits.h>

int	ft_pwd(t_hell *hell)
{
	char buf[PATH_MAX];
	char *success = NULL;
	success = getcwd(buf, sizeof(buf));
	if (success)
		return (printf("%s\n", buf), 1); // use fd
	return (1);
}