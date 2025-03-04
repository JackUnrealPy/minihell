/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:51:11 by agara             #+#    #+#             */
/*   Updated: 2024/09/02 18:02:34 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (8);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int	main(int argc, char** argv)
// {
// 	(void)argc;
// 	char	c;

// 	c = argv[1][0];
// 	printf("%d\n", ft_isalnum(c));
// 	printf("%d\n", isalnum(c));
// 	return 0;
// }