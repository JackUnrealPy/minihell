/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:03:52 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 12:10:56 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_digit(int num, int fd)
{
	int	first_digits;
	int	digit;

	digit = num +48;
	if (num / 10 == 0)
	{
		write(fd, &digit, 1);
		return ;
	}
	first_digits = num / 10;
	digit = (num % 10) + 48;
	print_digit(first_digits, fd);
	write(fd, &digit, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		print_digit(n * -1, fd);
	}
	else
		print_digit(n, fd);
}

// int main()
// {
// 	ft_putnbr_fd(123, 1);
// 	return 0;
// }