/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:03:40 by agara             #+#    #+#             */
/*   Updated: 2024/09/13 20:01:40 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src)
		return (dest);
	if (dest < src)
	{
		while (i < n)
		{
			*((char *)(dest + i)) = *((char *)(src + i));
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			*((char *)(dest + n - i - 1)) = *((char *)(src + n - i - 1));
			i++;
		}
	}
	return (dest);
}

// #include <stdio.h>
// int	main()
// {
// 	void	*dest;
// 	dest = malloc(64);
// 	int		src;
// 	src = 23;
// 	// int	*res;
// 	// res = ft_memmove(dest, &src, 4);
// 	ft_memmove(dest ,&src, 4);
// 	printf("%d\n",*(int *)dest);
// 	free(dest);
// 	return 0;
// }