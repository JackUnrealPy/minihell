/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:40 by agara             #+#    #+#             */
/*   Updated: 2024/09/13 16:05:29 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*res;

	if (ft_strlen(s) > len)
		res = malloc(sizeof(char) * (len + 1));
	else
		res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

// #include <stdio.h>
// int main()
// {
// 	char str[] = "abcdefgh";
// 	char *res;

// 	res = ft_substr(str, 8, 7);
// 	printf("%s", res);
// 	free(res);
// 	return 0;
// }