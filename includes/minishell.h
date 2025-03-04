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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>

// linked list with all the stuff to free
typedef struct	s_free
{
	void	*freeme;
	struct s_free	*next;
}	t_free;

// struct to have everything ,we should have only one instance of this
typedef struct	s_hell
{
	t_free	*freeme;
	char	**argv;
	char	**envp;

}	t_hell;



int		init(t_hell *hell, char **envp);
void	writeprompt(void);

void	parse(char *str);

void	jumpship(t_hell hell);

#endif