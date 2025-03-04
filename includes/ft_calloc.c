/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:02:47 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 12:02:48 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*res;
	size_t		i;

	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
		((char *)res)[i++] = '\0';
	return (res);
}

// int main()
// {
// 	char	*str;
// 	str = ft_calloc(5, sizeof(char));
// 	str[0] = '1';
// 	printf("%s", str);
// 	free(str);
// 	return 0;
// }
