/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:57:03 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/06/11 14:45:42 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(t_hell *hell, char *var, char *error, int exitcode)
{
	if (error)
	{
		if (var)
			ft_putstr_fd(var, STDERR_FILENO);
		ft_putendl_fd(error, STDERR_FILENO);
	}
	hell->lastexit = exitcode;
	hell->exec_error = 1;
	if (hell->cmd_count > 1)
		ft_close(hell);
}
