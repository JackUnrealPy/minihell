/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:54:35 by agara             #+#    #+#             */
/*   Updated: 2025/06/08 21:23:06 by nrumpfhu         ###   ########.fr       */
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
		if (!garbage)
			return ;
		if (*garbage)
			free(*garbage);
		*garbage = NULL;
		i++;
	}
	va_end(args);
}
