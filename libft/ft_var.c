/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:20:19 by gfranque          #+#    #+#             */
/*   Updated: 2022/09/06 12:55:09 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printfc(va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	return (ft_putchar(c));
}

int	ft_printfs(va_list ap)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 0;
	str = va_arg(ap, char *);
	if (str == NULL)
		return (ft_putstr("(null)"));
	else
	{
		while (str[i])
		{
			n = n + ft_putchar(str[i]);
			i++;
		}
		return (n);
	}
}

int	ft_printfp(va_list ap)
{
	void	*p;

	p = va_arg(ap, void *);
	if (p == NULL)
		return (ft_putstr("(nil)"));
	else
	{
		write(1, "0x", 2);
		return (ft_putnbr_base((unsigned long int)p, "0123456789abcdef") + 2);
	}
}

int	ft_printfd(va_list ap)
{
	int	nb;
	int	signe;

	signe = 0;
	nb = va_arg(ap, int);
	if (nb < 0)
	{
		write (1, "-", 1);
		signe++;
	}
	return (ft_putnbr(nb) + signe);
}

int	ft_printfi(va_list ap)
{
	int	nb;
	int	signe;

	signe = 0;
	nb = va_arg(ap, int);
	if (nb < 0)
	{
		write (1, "-", 1);
		signe++;
	}
	return (ft_putnbr(nb) + signe);
}
