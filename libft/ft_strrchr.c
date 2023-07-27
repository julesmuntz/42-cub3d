/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:50:51 by gfranque          #+#    #+#             */
/*   Updated: 2022/05/17 15:04:26 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)s;
	i = 0;
	j = 0;
	while (s[i])
		i++;
	while ((i - j) >= 0 && s[i - j] != (unsigned char)c)
		j++;
	if ((i - j) < 0)
		return (NULL);
	return (str + (i - j));
}
