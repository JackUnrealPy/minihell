/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:02:56 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 12:16:41 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getabs(int n)
{
	if (n >= 0)
		return (n);
	else
		return (-1 * n);
}

static void	revert(char *res)
{
	int		len;
	int		i;

	len = (int)(ft_strlen(res) - 1);
	i = 0;
	while (i < ((len + 1) / 2))
	{
		res[i] = *(res + i) ^ *(res + len - i);
		res[len - i] = *(res + i) ^ *(res + len - i);
		res[i] = *(res + i) ^ *(res + len - i);
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		temp;
	int		i;

	res = malloc(sizeof(char) * 12);
	if (!res)
		return (NULL);
	i = 0;
	temp = n;
	while (temp != 0)
	{
		res[i++] = (getabs(temp % 10)) + 48;
		temp /= 10;
	}
	if (n < 0)
		res[i++] = '-';
	if (n == 0)
		res[i++] = '0';
	res[i] = '\0';
	revert(res);
	return (res);
}

// int main()
// {
// 	char *res;
// 	res = ft_itoa(334);
// 	printf("%s", res);
// 	free(res);
// 	return 0;
// }