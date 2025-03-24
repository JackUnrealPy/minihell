#ifndef EXECUTION_H
# define EXECUTION_H

# include "includes/minishell.h"

// builtins
int	determine_builtin(t_hell *hell, t_proc *head, int pipe);
void	ft_echo(t_proc *head, int pipe);
int	ft_env(t_redir *redirs, char **envp, int pipe);
int	ft_pwd(t_redir *redirs, int pipe);

// environment vars
void	ft_double_strdup(t_hell *hell, char **envp);

// exec
int loop_cmds(t_hell *hell);

// pipes
void	ft_close(t_hell *hell);
void	ft_wait(t_proc *head);
void	initialise(t_proc *head, t_hell *hell);
void	create_cmd(t_proc *head);
void	first_child(t_proc *head, t_hell *hell);
void	middle_child(t_proc *head, t_hell *hell, int i);
void	ft_pipex(t_hell *hell);

// single command
void	ft_redirection(t_redir *redirs);
void	single_cmd(t_proc *head, char **envp);


#endif