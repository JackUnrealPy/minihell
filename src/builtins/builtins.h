#include "../../includes/minishell.h"
#include "../exec/pipex.h"

#include <linux/limits.h>

int     determine_builtin(int argc, char *argv[], char ***envp);
char	**export_init(int argc, char **argv, char **envp);
void	ft_cd(char **argv);
void	print_echo(char **args, int newline);
char	**ft_double_strdup(char **args);
void	ft_echo(char *argv[]);
void ft_unset(char **envp, char *var_to_delete);
void	env_export(char **envp, int fd);
void	ft_export(char **envp);
int     ft_pwd(char **argv);
int	ft_env(char **argv, char **envp, int fd);
void add_list_element(t_list *a, void *content);
char	**ft_realloc_envp(char **args, int new_element, char *new);
t_list *create_env_list(char **envp);