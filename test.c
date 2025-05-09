#include <stdio.h>
#include "includes/libft.h"
#include <string.h>

char	*ft_getenv(char *key, char **envp)
{
	char *value = NULL;
	int i = 0;
	int a = 0;
    int len = strlen(key);
	while (envp[i])
	{
		if (strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
            a = 1;
            while (envp[i] && envp[i][a+len] && envp[i][a+len] != '\n')
                a++;
            value = ft_substr(envp[i], len + 1, a - 1);
		}
        i++;
	}
	return(value);
}

int main(int argc, char **argv, char **envp)
{
	printf("%s\n", ft_getenv("zz", envp));
    printf("%s\n", getenv("zz"));
	(void)argc;
	(void)argv;
}