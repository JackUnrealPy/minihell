/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:13:40 by agara             #+#    #+#             */
/*   Updated: 2025/03/19 20:49:47 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../pipex/libft/libft.h"
# include "../execution.h"
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <errno.h>
# include <linux/limits.h>
# include <string.h>

// linked list with all the stuff to free
typedef struct	s_free
{
	int scope;
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
	t_free			*freeme;
	t_redir			*redirs;
	char			**cmd;
	char			*cmd_path;
	pid_t			pid;
	char			*input;
	struct s_proc	*next;
	struct s_proc	*prev;
}	t_proc;

// struct to have everything ,we should have only one instance of this

typedef struct	s_hell
{
	t_free	*freemeglobal;
	char	**argv;
	int 	argc;
	int		cmd_count;
	int		*pipe_fd;
	char	**envp;
	t_proc	**head;
	int		lastexit;

}	t_hell;



int		init(t_hell *hell, char **envp);
void	writeprompt(void);

void	parse(t_hell *hell, char *str);
t_proc	*create_proc(const char *cmd);

void	jumpship(t_hell hell);

int		ft_isspace(char c);

#endif