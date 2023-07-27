/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:25:16 by gfranque          #+#    #+#             */
/*   Updated: 2022/05/22 11:25:22 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		new->next = *lst;
		*lst = new;
	}
	return ;
}
/*
int	main(void)
{
	t_list	elem1;
	t_list	elem2;
	t_list	new;
	t_list	*lst;

	lst = &elem1;
	elem1.next = &elem2;
	elem2.next = 0;
	new.next = 0;
	elem1.content = "24";
	elem2.content = "42";
	new.content = "12";
	while (lst)
	{
		printf("lst %s\n", (char *)lst->content);
		lst = lst->next;
	}
	lst = &elem1;
	ft_lstadd_front(&lst, &new);
	while (lst)
	{
		printf("lst %s\n", (char *)lst->content);
		lst = lst->next;
	}
	return (0);
}
*/