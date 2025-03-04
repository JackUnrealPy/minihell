/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:03:37 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 20:21:14 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src && (n != 0))
		return (NULL);
	while (i < n)
	{
		*((char *)(dest + i)) = *((char *)(src + i));
		i++;
	}
	return (dest);
}

// int	main()
// {
// 	void	*dest;
// 	dest = malloc(64);
// 	int		src;
// 	src = 23;
// 	int	*res;
// 	res = ft_memcpy(dest, &src, 4);
// 	printf("%d\n",*res);
// 	free(dest);
// 	return 0;
// }