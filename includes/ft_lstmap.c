/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:02:26 by agara             #+#    #+#             */
/*   Updated: 2024/09/13 16:13:46 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*node;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	temp = lst->next;
	while (temp)
	{
		node = ft_lstnew(f(temp->content));
		ft_lstadd_back(&res, node);
		temp = temp->next;
	}
	return (res);
}
