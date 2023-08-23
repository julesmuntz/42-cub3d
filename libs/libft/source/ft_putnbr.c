/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 23:32:42 by gfranque          #+#    #+#             */
/*   Updated: 2022/09/06 12:55:25 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbrneg(int nb, int *ptr)
{
	if (nb < -9)
	{
		ft_putnbrneg(nb / 10, ptr);
		ft_putnbrneg(nb % 10, ptr);
	}
	else
	{
		nb = -nb;
		*ptr = *ptr + ft_putchar(nb + '0');
	}
	return ;
}

static void	ft_putnbrpos(int nb, int *ptr)
{
	if (nb < 0)
	{
		ft_putnbrneg(nb, ptr);
		return ;
	}
	if (nb > 9)
	{
		ft_putnbrpos(nb / 10, ptr);
		ft_putnbrpos(nb % 10, ptr);
	}
	else
		*ptr = *ptr + ft_putchar(nb + '0');
	return ;
}

int	ft_putnbr(int nb)
{
	int	ptr;

	ptr = 0;
	ft_putnbrpos(nb, &ptr);
	return (ptr);
}
