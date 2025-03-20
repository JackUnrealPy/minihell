/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:13:40 by agara             #+#    #+#             */
/*   Updated: 2025/03/20 20:35:08 by agara            ###   ########.fr       */
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
	int				type;
	t_redir			*redirs;
	char			**cmd;
	char			*input;
	struct s_proc	*next;
	struct s_proc	*prev;
}	t_proc;

// struct to have everything ,we should have only one instance of this

typedef struct	s_hell
{
	t_free	*freeme;
	char	**argv;
	char	**envp;
	t_proc	**head;

}	t_hell;



int		init(t_hell *hell, char **envp);
void	writeprompt(void);

void	parse(t_hell *hell, char *str);
t_proc	*create_proc(const char *cmd);

void	jumpship(t_hell hell);
void	ft_procclear(t_proc **proc);

int		ft_isspace(char c);

#endif