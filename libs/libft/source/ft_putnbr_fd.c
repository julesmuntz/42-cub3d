/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:41:31 by gfranque          #+#    #+#             */
/*   Updated: 2022/09/06 13:02:44 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnb(long int nb, int fd)
{
	if (nb > 9)
	{
		ft_putnb(nb / 10, fd);
		ft_putnb(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = (long int)n;
	if (nb < 0)
	{
		nb = nb * -1;
		write(fd, "-", 1);
	}
	ft_putnb(nb, fd);
	return ;
}
