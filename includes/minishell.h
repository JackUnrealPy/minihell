/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:13:40 by agara             #+#    #+#             */
/*   Updated: 2025/03/22 21:10:41 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

// linked list with all the stuff to free
typedef struct	s_free
{
	void	*freeme;
	struct s_free	*next;
}	t_free;

typedef	struct	s_redir
{
	int				type;
	char			*path;
	struct s_proc	*next;
}	t_redir;

typedef	struct	s_proc
{
	t_free			**freeme;
	t_redir			**redirs;
	char			**cmd;
	char			*input;
	struct s_proc	*next;
	struct s_proc	*prev;
}	t_proc;

// struct to have everything ,we should have only one instance of this

typedef struct	s_hell
{
	t_free	**freeme;
	char	**argv;
	char	**envp;
	t_proc	**head;

}	t_hell;



int		init(t_hell *hell, char **envp);
void	writeprompt(void);

void	local_init(t_hell *hell, char *cmd);
void	parse(t_hell *hell, char *str);

// Alloctracker
void	*ft_malloc(t_free **head, void *obj);

// cleares a t_free llist
void	throw_garbage(t_free **head);

// clears all memory and exits
void	jump_ship(t_hell *hell, short int exitcode);

void	sysntaxerr();

//	 Utils
void	close_proc(t_hell *hell);
t_proc	*create_proc(t_hell *hell);
void	addproc(t_proc **head, t_proc *next);

// void	ft_procclear(t_proc **proc);

int		ft_isspace(char c);
int		ismeta(char *c);
#endif