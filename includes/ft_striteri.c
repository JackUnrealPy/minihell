/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:09 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 12:42:37 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, (s + i));
		i++;
	}
}

// void	ttolower(unsigned int i, char *c)
// {
// 	if (*c <= 90 && *c >= 65)
// 		*c += ('a' - 'A');
// }

// int main()
// {
// 	char	test[] = "abCCde";
// 	ft_striteri(test, ttolower);
// 	printf("%s", test);
// 	return 0;
// }