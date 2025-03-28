/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:13:40 by agara             #+#    #+#             */
/*   Updated: 2025/03/25 19:01:00 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <errno.h>
# include <string.h>

// linked list with all the stuff to free
typedef struct	s_free
{
	void	*freeme;
	struct s_free	*next;
}	t_free;

typedef	struct	s_redir
{
	int				type; // 0 input, 1output with trunc, 2output with append, 3heredoc
	char			*pathordel;
	struct s_redir	*next;
}	t_redir;


typedef	struct	s_proc
{
	t_free			**freeme;
	t_redir			**redirs;
	char			**cmd;
	char			*cmd_path;
	pid_t			pid;
	pid_t			hpid;
	struct s_proc	*next;
	struct s_proc	*prev;
}	t_proc;

// struct to have everything ,we should have only one instance of this
typedef struct	s_hell
{
	t_free	**freeme;
	char	**argv;
	int 	argc;
	int		cmd_count;
	int		hdoc_count;
	int		*pipe_fd;
	int		*hdoc_fd;
	char	**envp;
	t_proc	**head;
	int		lastexit;

}	t_hell;

// EXECUTION

// builtins
int	determine_builtin(t_hell *hell, t_proc *head, int pipe);
void	ft_echo(t_proc *head, int pipe);
int	ft_env(t_redir *redirs, char **envp, int pipe);
int	ft_pwd(t_redir *redirs, int pipe);
void ft_unset(char **envp, char *var_to_delete);

// environment vars
void	ft_double_strdup(t_hell *hell, char **envp);

// exec
int loop_cmds(t_hell *hell, char **envp);

// pipes
void	initialise_pipes(t_hell *hell, t_proc *head, t_redir *redirs);
void	create_cmd(t_proc *head);
void	children(t_proc *head, t_hell *hell, int i);
void	ft_pipex(t_hell *hell);

// heredoc
int		heredoc_check(t_redir *redirs);
void	init_hdoc(t_hell *hell, t_proc *head, int i);
void    heredoc(t_hell *hell, t_proc *head, t_redir *redirs, int i);
int     hdoc_pipes(t_hell *hell, t_proc *head);

// redirection
void	input_redirection(t_hell *hell, t_proc *head, int i);
void	output_redirection(t_hell *hell, t_proc *head, int i);

// single command
void	single_cmd(t_hell *hell, t_proc *head);

// helpers
void	ft_close(t_hell *hell);
void	ft_wait(t_hell *hell);
void	initialise_struct( t_hell *hell, t_proc *head);


// void	local_init(t_hell *hell, char *cmd);
int		init(t_hell *hell, char **envp);
void	writeprompt(void);

void	parse(t_hell *hell, char *str);
// Alloctracker
void	*ft_malloc(t_free **head, void *obj);

// cleares a t_free llist
void	throw_garbage(t_free **head);

// clears all memory and exits
void	jump_ship(t_hell *hell, short int exitcode);

void	sysntaxerr();

void	local_init(t_hell *hell, char *cmd);
//	 Utils
void	close_proc(t_hell *hell);
t_proc	*create_proc(t_hell *hell);
void	addproc(t_proc **head, t_proc *next);

// void	ft_procclear(t_proc **proc);

int		ft_isspace(char c);
int		ismeta(char *c);
#endif