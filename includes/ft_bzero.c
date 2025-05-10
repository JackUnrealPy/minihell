/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:02:41 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 14:47:23 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = '\0';
}

// #include <stdio.h>
// int main()
// {
// 	char	test[] = "abc";
// 	printf("%s", test);	
// 	ft_bzero(test, 4);
// 	printf("%s", test);	
// 	return 0;
// }