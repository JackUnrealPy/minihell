/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:34 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 21:22:28 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		len;

	len = (int)ft_strlen(str) - 1;
	i = 0;
	if (!(char)c)
	{
		while (str[i])
			i++;
		return ((char *)(str + i));
	}
	while (i <= len)
	{
		if (str[len - i] == (char)c)
			return ((char *)(str + len - i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// int main()
// {
// 	char *str;
// 	str = "acacbajbca";
// 	printf("%s",ft_strrchr(str, 'a'));
// 	return 0;
// }