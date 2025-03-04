/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:08:29 by agara             #+#    #+#             */
/*   Updated: 2024/09/02 18:02:42 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii( int c)

{
	if ((c >= 0 && c <= 127))
		return (1);
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
// 	printf("%d\n", ft_isascii(c));
// 	printf("%d\n", isascii(c));
// 	return 0;
// }