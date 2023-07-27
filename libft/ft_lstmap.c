/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:33:14 by gfranque          #+#    #+#             */
/*   Updated: 2022/05/23 22:29:08 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lsstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst)
	{
		if (*lst)
		{
			while (*lst)
			{
				temp = (*lst)->next;
				ft_lstdelone(*lst, del);
				*lst = temp;
			}
		}
	lst = NULL;
	}
	return ;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*begin;

	if (lst || (*f) || (*del))
	{
		newlst = ft_lstnew((*f)(lst->content));
		if (!newlst)
			return (NULL);
		begin = newlst;
		lst = lst->next;
		while (lst)
		{
			newlst->next = ft_lstnew((*f)(lst->content));
			if (!newlst->next)
			{
				ft_lsstclear(&begin, del);
				return (NULL);
			}
			lst = lst->next;
			newlst = newlst->next;
		}
		return (begin);
	}
	return (NULL);
}
