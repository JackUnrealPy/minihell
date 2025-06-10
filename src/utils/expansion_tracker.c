/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tracker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:43:01 by agara             #+#    #+#             */
/*   Updated: 2025/06/10 13:43:02 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_immun(int *exp, int num)
{
	int	i;

	i = 0;
	while (exp[i] != -1 && exp[i] <= num)
	{
		if (exp[i + 1] >= num)
			return (1);
		i += 2;
	}
	return (0);
}

void	add_num(t_hell *hell, int **ptr, int num)
{
	int	*new;
	int	i;

	if (!*ptr)
	{
		*ptr = malloc(sizeof(int) * 2);
		if (!(*ptr))
			jump_ship(hell, 1);
		(*ptr)[0] = num;
		(*ptr)[1] = -1;
		return ;
	}
	i = -1;
	while ((*ptr)[++i] != -1)
		;
	new = malloc(sizeof(int) * (i + 2));
	if (!new)
		jump_ship(hell, 1);
	i = -1;
	while ((*ptr)[++i] != -1)
		new[i] = (*ptr)[i];
	new[i] = num;
	new[i + 1] = -1;
	ft_terminate(1, ptr);
	*ptr = new;
}

int	get_last_num(int *nums)
{
	int	i;

	i = 0;
	while (nums[i] != -1)
		i++;
	if (i)
		return (nums[i - 1]);
	return (-1);
}
