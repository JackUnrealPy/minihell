/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:20:55 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/05/21 14:58:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			if (!s1[i] || s2[i])
				return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

/*
int main(void)
{
	char s1[] = "ABA";
	char s2[] = "ABC";
	printf("%i\n", ft_strcmp(s1, s2));
	printf("%i", strcmp(s1, s2));
}
*/
