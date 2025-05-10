/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:03:03 by agara             #+#    #+#             */
/*   Updated: 2024/09/11 12:15:25 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

// int main()
// {
// 	t_list	*lst;
// 	t_list	*new_node;

// 	int		a;
// 	int		b;

// 	a = 5;
// 	b = 9;
// 	lst = ft_lstnew(&a);
// 	new_node = ft_lstnew(&b);
// 	ft_lstadd_front(&lst, new_node);
// 	printf("%d %d\n",*((int *)lst->content), *((int *)new_node->content) );

// 	return 0;
// }