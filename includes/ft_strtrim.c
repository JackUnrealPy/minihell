/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:18:23 by agara             #+#    #+#             */
/*   Updated: 2024/09/13 13:29:01 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getend(char const *str, char const *set)
{
	int	i;
	int	j;
	int	inset;

	inset = 1;
	i = (int)ft_strlen(str) - 1;
	while (i > 0 && inset == 1)
	{
		inset = 0;
		j = 0;
		while (inset == 0 && set[j])
		{
			if (set[j++] == str[i])
				inset = 1;
		}
		i--;
	}
	return (i + 2);
}

static int	getstart(char const *str, char const *set)
{
	int	i;
	int	j;
	int	inset;

	inset = 1;
	i = 0;
	while (str[i] && inset == 1)
	{
		inset = 0;
		j = 0;
		while (inset == 0 && set[j])
		{
			if (set[j++] == str[i])
				inset = 1;
		}
		i++;
	}
	return (i - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	if (!s1)
		return (NULL);
	if (!set || (ft_strlen(s1) == 0))
		return (ft_strdup(s1));
	start = getstart(s1, set);
	end = getend(s1, set);
	if ((end - start + 1) < 0)
		res = malloc(1);
	else
		res = malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < (end - start))
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// #include <stdio.h>
// int main()
// {
// 	char	set[] = " \n\t";
// 	char	str[] = "  \t \t \n   \n\n\n\t";
// 	char	*trimmed = ft_strtrim(str, set);
// 	printf("%s", trimmed);
// 	free(trimmed);
// 	return 0;
// }