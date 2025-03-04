/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:03:07 by agara             #+#    #+#             */
/*   Updated: 2024/09/13 15:30:03 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	void	*tempnext;

	if (!del || !*lst)
		return ;
	while (*lst)
	{
		tempnext = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tempnext;
	}
}
