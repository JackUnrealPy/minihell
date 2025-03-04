/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:16 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 21:34:19 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
	{
	size_t	srclen;
	size_t	destlen;
	size_t	i;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	i = 0;
	while (i < srclen && ((destlen + i) < (dsize - 1)))
	{
		if ((destlen + i) < dsize)
			dest[destlen + i] = src[i];
		i++;
	}
	if (dsize != 0)
		dest[destlen + i] = '\0';
	if (destlen < dsize)
		return (srclen + destlen);
	else
		return (srclen + dsize);
}

// int	main()
// {

// 	char dest[7] = "asd";
// 	char src[8] =	"vvv";
// 	printf("src %s dest %s\n",src, dest);
// 	printf("%zu\n",ft_strlcat("pqrstuvwxyz", "abcd", 0));
// 	printf("src %s dest %s",src, dest);
// 	return 0;
// }