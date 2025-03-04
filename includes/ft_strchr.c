/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:03 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 21:22:21 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int search_str)
{
	int		i;

	i = 0;
	if (!(char)search_str)
	{
		while (str[i])
			i++;
		return ((char *)str + i);
	}
	while (str[i])
	{
		if (str[i] == (char)search_str)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// int main()
// {
// 	char *str;
// 	str = "acacajca";
// 	printf("%s",ft_strchr(str, 'b'));
// 	return 0;
// }