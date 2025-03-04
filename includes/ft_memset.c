/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:10:24 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 14:45:21 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// int main(int argc, char** argv)
// {
// 	(void) argc;
// 	char dest[4];
// 	char c;

// 	c = 'a';
// 	ft_memset(dest, c, 2);
// 	printf("%s",dest);

// 	return 0;
// }