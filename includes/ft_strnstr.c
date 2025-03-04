/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:31 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 21:13:30 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	unsigned int		i;
	unsigned int		j;
	char				*res;

	res = (char *)big;
	if (small == big || ft_strlen(small) == 0)
		return (res);
	i = 0;
	while (i < len && res[i])
	{
		j = 0;
		while (res[i + j] && res[i + j] == small[j] && (len > (i + j)))
			j++;
		if (j == (unsigned int)ft_strlen(small))
			return (res + i);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// int main()
// {
// 	char big[9] = "acbbabrr";
// 	char small[4] = "bb";
// 	printf("%s",ft_strnstr(big, small,4) );
// 	return 0;
// }