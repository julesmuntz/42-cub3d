/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:44:53 by gfranque          #+#    #+#             */
/*   Updated: 2022/05/10 11:42:18 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*strsrc;
	char	*strdest;

	i = 0;
	strsrc = (void *)src;
	strdest = dest;
	if (n == 0)
		return (dest);
	while (i <= (n - 1))
	{
		strdest[i] = strsrc[i];
		i++;
	}
	return (dest);
}
