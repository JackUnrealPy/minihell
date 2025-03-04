/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:47:01 by agara             #+#    #+#             */
/*   Updated: 2024/09/02 18:02:47 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)

{
	if ((c >= 48 && c <= 57))
		return (2048);
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
// 	printf("%d\n", ft_isdigit(c));
// 	printf("%d\n", isdigit(c));
// 	return 0;
// }