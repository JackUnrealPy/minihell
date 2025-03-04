/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:19 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 21:16:28 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dsize)
{
	unsigned int		srclen;
	size_t				i;

	srclen = ft_strlen(src);
	if (!dsize)
		return (srclen);
	i = 0;
	while ((i < srclen) && (i < dsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;

// 	char *dest = argv[1];
// 	char *src =	argv[2];
// 	char *dest1 = argv[3];
// 	char *src1 =	argv[4];
// 	printf("%ld\n", ft_strlcpy(dest, src, 2));
// 	printf("src %s dest %s\n",src, dest);
// 	printf("%ld\n", strlcpy(dest1, src1, 2));
// 	printf("src1 %s dest1 %s",src1, dest1);
// 	return 0;
// }