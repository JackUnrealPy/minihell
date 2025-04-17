/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:03:58 by agara             #+#    #+#             */
/*   Updated: 2025/04/17 20:42:03 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	inset(char const *s, char const c)
{
	int	i;

	i = -1;
	if (!s || !c || !s[0])
		return (0);
	while (s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

static int	countwords(char const *s, char *charset)
{
	int	i;
	int	inword;
	int	res;

	res = 0;
	inword = 0;
	i = -1;
	while (s[++i])
	{
		if (!inset(charset, s[i]) && !inword)
		{
			res++;
			inword = 1;
		}
		else if (inword && inset(charset, s[i]))
			inword = 0;
	}
	if (!res && s[0])
		res++;
	return (res);
}

static char	*getword(char const *s, char *charset)
{
	int		i;
	char	*res;

	i = -1;
	while (s[++i])
	{
		if (inset(charset, s[i]))
			break ;
	}
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (s[++i])
	{
		if (inset(charset, s[i]))
			break ;
		res[i] = s[i];
	}
	res[i] = 0;
	return (res);
}

char	**ft_split(char const *s, char *charset)
{
	char	**res;
	int		i;
	int		j;

	if (!s || !s[0])
		return (NULL);
	if (!countwords(s, charset))
		return (NULL);
	res = malloc(sizeof(char *) * (countwords(s, charset) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!inset(charset, s[i]))
		{
			res[j++] = getword(s + i, charset);
			while (s[i] && !inset(charset, s[i]))
				i++; // i incrementation was wrong before
		}
		else
			i++;
	}
	res[j] = NULL; // here it was j + 1

	return (res);
}

// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	char	**res;
// 	int		i;

// 	res = ft_split(argv[1], argv[2]);
// 	if (!res)
// 		return 0;
// 	i = 0;
// 	while(res[i])
// 		printf("[%s]", res[i++]);
// 	i = 0;
// 	while(res[i])
// 	{
// 		free(res[i]);
// 		i++;
// 	}
// 	free(res);	
// 	return 0;
// }