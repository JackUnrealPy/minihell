/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:44 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 12:04:44 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c <= 90 && c >= 65)
		c += ('a' - 'A');
	return (c);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%c",(char)ft_tolower('D'));
// 	return 0;
// }