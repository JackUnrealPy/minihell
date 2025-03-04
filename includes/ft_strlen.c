/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:58:53 by agara             #+#    #+#             */
/*   Updated: 2024/09/02 18:37:31 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

// #include <stdio.h>
// int main(int argc, char** argv)
// {
// 	(void)argc;
// 	printf("%lu\n", strlen(argv [1]));
// 	printf("%zu\n", ft_strlen(argv [1]));
// }