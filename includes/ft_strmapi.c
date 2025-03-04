/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:24 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 12:08:11 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;

	i = 0;
	if (!s || ! f)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

// char	ttolower(unsigned int i, char c)
// {
// 	(void) i;
// 	if (c <= 90 && c >= 65)
// 		c += ('a' - 'A');
// 	return (c);
// }

// #include <stdio.h>
// int main()
// {
// 	char	test[] = "abCCde";
// 	char	*res;
// 	res = ft_strmapi(test, ttolower);
// 	printf("%s", res);
// 	free(res);
// 	return 0;
// }