/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:03:58 by agara             #+#    #+#             */
/*   Updated: 2024/09/13 19:55:41 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*getword(int *index, char const *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[*index + i] && str[*index + i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[*index] && str[*index] != c)
		word[i++] = str[(*index)++];
	word[i] = '\0';
	return (word);
}

static int	countwords(char const *s, char c)
{
	int	count;
	int	i;
	int	inword;

	count = 0;
	i = 0;
	inword = 0;
	while (s[i])
	{
		if (s[i] != c && inword == 0)
		{
			count++;
			inword = 1;
		}
		else if (s[i] == c && inword == 1)
			inword = 0;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			res[j++] = getword(&i, s, c);
			if (!res[j - 1])
				return (ft_cleanstrarr(res), NULL);
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}

// #include <stdio.h>
// int main()
// {
// 	char	str[] = "aadddavadddvvaa";
// 	char	**res;
// 	int		i;

// 	res = ft_split(str, 'd');
// 	i = 0;
// 	while(res[i])
// 		printf("%s  ", res[i++]);
// 	i = 0;
// 	// while(res[i])
// 	// {
// 	// 	free(res[i]);
// 	// 	i++;
// 	// }
// 	free(res);	
// 	return 0;
// }