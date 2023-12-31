/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:56:28 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/27 15:47:55 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is(int (*f)(int), char *str)
{
	int	i;

	i = 0;
	while (str[i] && (*f)(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}
