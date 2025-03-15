/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:13:40 by agara             #+#    #+#             */
/*   Updated: 2025/03/04 20:16:03 by agara            ###   ########.fr       */
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

typedef	struct	s_proc
{
	int				type;
	struct s_proc	*next;
	struct s_proc	*prev;
	char			*cmd;
	int				fds[2];
}	t_proc;

// struct to have everything ,we should have only one instance of this

typedef struct	s_hell
{
	t_free	*freeme;
	char	**argv;
	char	**envp;
	t_proc	*head;

}	t_hell;



int		init(t_hell *hell, char **envp);
void	writeprompt(void);

void	parse(t_hell *hell, const char *str);
t_proc	*create_proc(const char *cmd);

void	jumpship(t_hell hell);

#endif