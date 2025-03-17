#include "../pipex/pipex.h"
#include <linux/limits.h>

int	determine_builtin(char *argv[], char **envp);
void	ft_cd(char **argv);
void	print_echo(char **args, int newline);
char	**ft_double_strdup(char **args);
void	ft_echo(char *argv[]);
void	ft_env(char **envp, int fd);
void	env_export(char **envp, int fd);
void	ft_export(char **envp);
void	ft_pwd(char **argv);