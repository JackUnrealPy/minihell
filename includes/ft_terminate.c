/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:54:35 by agara             #+#    #+#             */
/*   Updated: 2025/01/16 21:54:35 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_terminate(int count, ...)
{
	va_list	args;
	char	**garbage;
	int		i;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		garbage = va_arg(args, char **);
		if (*garbage)
			free(*garbage);
		*garbage = NULL;
		i++;
	}
	va_end(args);
}
