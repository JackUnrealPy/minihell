/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:50:23 by agara             #+#    #+#             */
/*   Updated: 2025/03/19 19:31:43 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ismeta(char *c)
{
	if (*c == '|')
		return (*c);
	if (*c == '<')
	{
		if (*(c + 1) == '<')
			return ('-');
		return (*c);
	}
	if (*c == '>')
	{
		if (*(c + 1) == '>')
			return ('+');
		return (*c);
	}
	return (0);
}
