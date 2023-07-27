/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:09:37 by gfranque          #+#    #+#             */
/*   Updated: 2022/09/06 12:55:34 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnb(unsigned long int n, char *base, int *ptr)
{
	unsigned int	len;

	len = 0;
	while (base[len])
		len++;
	if (n >= len)
	{
		ft_putnb((n / len), base, ptr);
		ft_putnb((n % len), base, ptr);
	}
	else
		*ptr = *ptr + ft_putchar(base[n]);
}

int	ft_putnbr_base(unsigned long int n, char *base)
{
	int	ptr;

	ptr = 0;
	ft_putnb(n, base, &ptr);
	return (ptr);
}
