/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:19:15 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 17:24:52 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_hell *hell)
{
	char	pwd[PATH_MAX];
	char	*success;

	success = getcwd(pwd, PATH_MAX);
	if (!success)
	{
		ft_putendl_fd("getcwd failed", 2);
		jump_ship(hell, 1);
	}
	ft_putendl_fd(pwd, 1);
	return (1);
}
