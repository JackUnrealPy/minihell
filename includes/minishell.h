/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:13:40 by agara             #+#    #+#             */
/*   Updated: 2025/06/11 21:16:44 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

// linked list with all the stuff to free
typedef struct s_free
{
	void			*freeme;
	struct s_free	*next;
}					t_free;

typedef struct s_token
{
	void			*token;
	struct s_token	*next;
	struct s_token	*prev;
	int				*expansion;
}					t_token;

typedef struct s_redir
{
	int				type;
	char			*pathordel;
	t_token			*redt;
	struct s_redir	*next;
}					t_redir;

typedef struct s_proc
{
	t_token			**tokens;
	t_free			**freeme;
	t_redir			**redirs;
	char			**cmd;
	int				redirerr;
	char			*cmd_path;
	pid_t			pid;
	int				hdoc_present;
	char			*hdoc_tmpfile;
	int				hdoc_fd;
	struct s_proc	*next;
	struct s_proc	*prev;
	int				var;
}					t_proc;

// struct to have everything ,we should have only one instance of this
typedef struct s_hell
{
	t_free			**freeme;
	t_token			**tokens;
	t_proc			**head;
	char			**argv;
	char			**test;
	int				argc;
	int				cmd_count;
	int				exec_error;
	int				*pipe_fd;
	char			**localvars;
	char			**envp;
	int				lastexit;
	int				syntaxerr;
	char			*cmd;
	char			*hdoc_cmd;
	int				hdoc_sig;
}					t_hell;

// SIGNALS
void				handle_sig(int sig);

// EXECUTION

// builtins
void				ft_echo(t_proc *head);
int					ft_env(char **envp);
int					ft_pwd(t_hell *hell);
void				ft_unset(char **envp, char **var_to_delete);
void				ft_exit(t_hell *hell, t_proc *head, int pipe);
void				ft_export(t_hell *hell, t_proc *head);
void				ft_cd(t_hell *hell, t_proc *head);

// builtins helpers
long				ft_atol(const char *str);
int					is_builtin(t_proc *head);
int					determine_builtin(t_hell *hell, t_proc *head, int pipe);
int					builtins_output(t_hell *hell, t_proc *head);
int					built_err(t_hell *hell, char *type, char *msg, int exitnum);

// environment
char				*get_key(char *new);
int					is_append(char *envp, char *key, char *new, int len);
int					is_replace(char *envp, char *key, char *new, int len);
char				**ft_double_strdup(t_hell *hell, char **envp);
char				*ft_getenv(char *key, char **envp, int print_key);
char				**ft_realloc_envp(char **envp, int new_element, char **new);

// exec
int					loop_cmds(t_hell *hell);

// pipes
void				initialise_pipes(t_hell *hell, t_proc *head,
						t_redir *redirs);
void				create_cmd(t_hell *hell, t_proc *head);
void				children(t_proc *head, t_hell *hell, int i);
void				ft_pipex(t_hell *hell);

// heredoc
int					heredoc(t_hell *hell, t_proc *head, t_redir *redirs);
void				generate_tmpfile(t_hell *hell, t_proc *head);
void				expansion_heredoc(t_hell *hell, t_proc *head,
						char **buffer);
int					break_heredoc(t_redir *redirs, char *buffer);

// redirection
void				redirection(t_hell *hell, t_proc *head, int i);

// single command
void				single_cmd(t_hell *hell, t_proc *head);

// helpers
int					all_whitespace(char *cmd);
int					is_directory(char *cmd);
void				ft_freeme(char **arr);
void				ft_close(t_hell *hell);
void				ft_wait(t_hell *hell);
void				initialise_struct(t_hell *hell, t_proc *head);
void				error_msg(t_hell *hell, char *var, char *error,
						int exitcode);

// Init
void				local_init(t_hell *hell, char *cmd);
int					init(t_hell *hell, char **envp);
void				init_mem(t_hell *hell, char *pwd_env, char *env,
						char **split);

// Parse

void				parse(t_hell *hell, char *cmd);
void				tokenize(t_hell *hell, char *cmd);
void				divide_procs(t_hell *hell, t_proc *proc);
void				parse_expand(t_hell *hell, t_proc *proc, t_token **tokens);
char				*get_exp(t_hell *hell, t_proc *proc, char *str, int *i);
int					get_quotelen(char *cmd);
void				purge_quotes(t_hell *hell, t_proc *proc, t_token **v);
void				parse_redirs(t_hell *hell, t_proc *proc, t_token **v);
int					gen_redir(t_hell *hell, t_proc *proc,
						t_redir *red, t_token **token);

// Alloctracker
void				*ft_malloc(t_hell *hell, t_free **head, void *obj);
void				**ft_mallocarr(t_hell *hell, t_free **head, void **obj);
// Deletes by obj pointer or if all==1 deletes all tokens
void				pop_token(t_token **head, void *ptr, int all);
void				pop_free(t_free **head, void *ptr);

// cleares a t_free llist
void				throw_garbage(t_free **head);

// clears all memory and exits
void				jump_ship(t_hell *hell, short int exitcode);

//	Utils
//		Parse utils
void				word_split(t_hell *hell, t_proc *proc, t_token **v);
void				ft_update_cmd(t_hell *hell, t_proc *proc, char **cmd,
						char *str);
void				ft_update_token(t_hell *hell, t_token *token, int pos,
						char *str);
void				add_token(t_hell *hell, t_token **tokens, char *val);
void				del_token(t_token **tokens, t_token *token);
void				add_num(t_hell *hell, int **ptr, int num);
int					get_last_num(int *nums);
void				divide_tokens(t_hell *hell, t_token *token, int pos,
						int spaces);
t_token				*cut_token(t_token **tokens, t_token *token);
int					is_immun(int *exp, int num);
int					ft_update_quote(t_hell *hell, t_token *token, int pos);

// 		Proc utils
t_proc				*get_last_proc(t_proc **head);
void				close_proc(t_hell *hell);
t_proc				*create_proc(t_hell *hell);
void				addproc(t_proc **head, t_proc *next);

//		String utils
int					ft_isspace(char c);
int					ismeta(char *c);

// 		Exit utils
void				sysntaxerr(t_hell *hell, char *token, int len);

// dev		tooks for development
void				print_list(t_proc *a);

#endif