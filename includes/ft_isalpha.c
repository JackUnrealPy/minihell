/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:43 by agara             #+#    #+#             */
/*   Updated: 2024/09/02 18:02:38 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122))
		return (1024);
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
// 	printf("%d\n", ft_isalpha(c));
// 	printf("%d\n", isalpha(c));
// 	return 0;
// }