/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:03:27 by agara             #+#    #+#             */
/*   Updated: 2024/09/13 16:08:28 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	if (!lst)
		return (0);
	temp = lst;
	i = 1;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

// static void	*toa(void *s)
// {
// 	int		i;
// 	char	*res;

// 	res = malloc(4);
// 	i = 0;
// 	while (((char *)s)[i])
// 		res[i++] = 'A';
// 	return (res);
// }

// // void	toaiter(void *cont)
// // {
// // 	printf("from func %s\n", (char *)cont);
// // 	((char *)cont)[0] = 'A';
// // 	printf("after func %s\n", (char *)cont);
// // }

// void	delstr(void *content)
// {
// 	free((char *)content);
// }

// int main()
// {
// 	t_list	*lst;
// 	t_list	*new_node;
// 	t_list	*final;

// 	char 	*a;
// 	char	*b;
// 	char	*c;

// 	a = ft_strdup("aaa");
// 	lst = ft_lstnew(a);

// 	b = ft_strdup("bbb");
// 	new_node = ft_lstnew(b);
// 	ft_lstadd_front(&lst, new_node);

// 	c = ft_strdup("ccc");
// 	new_node = ft_lstnew(c);
// 	ft_lstadd_front(&lst, new_node);

// 	// ft_lstiter(lst, &toaiter);
// 	final = ft_lstmap(lst, &toa, &delstr);
// 	// printf("%s \n", ((char *)final->content) );

// 	// ft_lstclear(&(lst->next), &delstr);
// 	// ft_lstclear(&final, &delstr);
// 	if (!final)
// 		return 0;
// 	while (final)
// 	{
// 		printf("try\n");
// 		printf("%s \n",(char *)final->content);
// 		final = final->next;
// 	}
// 	return 0;
// }