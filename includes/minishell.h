/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:13:40 by agara             #+#    #+#             */
/*   Updated: 2025/05/17 22:54:11 by nrumpfhu         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>

// linked list with all the stuff to free
typedef struct	s_free
{
	void	*freeme;
	struct s_free	*next;
}	t_free;

typedef	struct	s_redir
{
	int				type; // 0 input, 1output with trunc, 2output with append, 3heredoc with quotes, 4 heredoc without quotes
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
	int				hdoc_present;
	char			*hdoc_tmpfile;
	int				hdoc_fd;
	struct s_proc	*next;
	struct s_proc	*prev;
	int				var;
}	t_proc;

// struct to have everything ,we should have only one instance of this
typedef struct	s_hell
{
	t_free	**freeme;
	char	**argv;
	char	**test;
	int 	argc;
	int		cmd_count;
	int		exec_error;
	int		*pipe_fd;
	char	**localvars;
	char	**envp;
	t_proc	**head;
	int		lastexit;
	int		syntaxerr;
}	t_hell;

// EXECUTION

// builtins
void	ft_echo(t_hell *hell, t_proc *head, int pipe);
int	ft_env(t_redir *redirs, char **envp, int pipe);
int	ft_pwd(t_hell *hell, t_redir *redirs, int pipe);
void ft_unset(t_hell *hell, char **envp, char *var_to_delete);
void	ft_exit(t_hell *hell, t_proc *head, int pipe);
void	ft_export(t_hell *hell, t_proc *head);
void	ft_cd(t_hell *hell, t_proc *head);

// builtins helpers
long	ft_atol(const char *str);
int	determine_builtin(t_hell *hell, t_proc *head, int pipe);
int	builtins_output(t_hell *hell, t_proc *head);
int	built_err(t_hell *hell, char *type, char *msg, int exitnum);

// environment
char	*get_key(char *new);
int	is_append(char *envp, char *key, char *new, int len);
int	is_replace(char *envp, char *key, char *new, int len);
char **	ft_double_strdup(t_hell *hell, char **envp);
char	*ft_getenv(char *key, char **envp, int print_key);
char	**ft_realloc_envp(t_hell *hell, char **envp, int new_element, char *new);

// exec
int loop_cmds(t_hell *hell);

// pipes
void	initialise_pipes(t_hell *hell, t_proc *head, t_redir *redirs);
void	create_cmd(t_hell *hell, t_proc *head);
void	children(t_proc *head, t_hell *hell, int i);
void	ft_pipex(t_hell *hell);

// heredoc
int	heredoc(t_hell *hell, t_proc *head, t_redir *redirs);
void	generate_tmpfile(t_hell *hell, t_proc *head);
void	expansion_heredoc(t_hell *hell, t_proc *head, char *buffer, char *tmp);
int	break_heredoc(t_redir *redirs, char *buffer);

// redirection
void	redirection(t_hell *hell, t_proc *head, int i);

// single command
void	single_cmd(t_hell *hell, t_proc *head);

// helpers
void	ft_freeme(char **arr);
void	ft_close(t_hell *hell);
void	ft_wait(t_hell *hell);
void	initialise_struct( t_hell *hell, t_proc *head);
void    error_msg(t_hell *hell, char* var, char *error, int exitcode);

// Init
void	local_init(t_hell *hell, char *cmd);
int		init(t_hell *hell, char **envp);
void	writeprompt(void);

void	parse(t_hell *hell, char *cmd, t_proc *proc);
int		ft_expand(t_hell *hell, t_proc *proc, char **str, int pos);
int	handle_quote(t_hell *hell, t_proc *proc, char **cmd, int pos);
char	*get_squote(t_hell *hell, t_proc *proc, char *quote);
char	*get_dquote(t_hell *hell, t_proc *proc, char **cmd, int pos);
int	get_quotelen(char *cmd);
int		get_redir(t_hell *hell, t_proc *proc, char *str);
void	add_arr_to_cmdarr(t_hell *hell, t_proc *proc, char **addme);
void	add_to_cmdarr(t_hell *hell, t_proc *proc, char *addme);
int	get_cmdarr(t_hell *hell, t_proc *proc, char **ptr, int i);


// Alloctracker
void	*ft_malloc(t_hell *hell, t_free **head, void *obj);
void	**ft_mallocarr(t_hell *hell, t_free **head, void **obj);

// cleares a t_free llist
void	throw_garbage(t_free **head);

// clears all memory and exits
void	jump_ship(t_hell *hell, short int exitcode);

//	Utils
// 		Proc utils
void	close_proc(t_hell *hell);
t_proc	*create_proc(t_hell *hell);
void	addproc(t_proc **head, t_proc *next);

//		String utils
void	add_arr_to_cmdarr(t_hell *hell, t_proc *proc, char **addme);
int		ft_isspace(char c);
int		ismeta(char *c);

// 		Exit utils
void	sysntaxerr(t_hell *hell, char* token, int len);

// dev		tooks for development
void 	print_list(t_proc *a);

#endif