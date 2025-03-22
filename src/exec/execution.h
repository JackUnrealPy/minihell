#include "../../includes/minishell.h"

// typedef struct s_hell
// {
// 	char **cmd;
// 	int argc;
//     char *path;
// 	char **argv;
// 	char *input_redir;
// 	char *output_redir;
// 	char *append;
//     pid_t pid;
// }		t_hell;

// env_list.c
t_list	*create_env_list(char **envp);
void	print_list(t_list *a);

//heredoc.c
void	free_heredoc(char *delimitor, char *txt, char *path);
int		redirection(int argc, char **argv);
void	heredoc(int argc, char **argv);