/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:16:14 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 14:43:21 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if ((c >= 32 && c <= 126))
		return (16384);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int	main(int argc, char** cv)
// {
// 	(void)argc;
// 	char	c;
// 	c = cv[1][0];
// 	printf("%d\n", ft_isprint(c));
// 	printf("%d\n", isprint(c));
// 	return 0;
// }