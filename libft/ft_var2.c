/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:32:55 by gfranque          #+#    #+#             */
/*   Updated: 2022/09/06 12:55:04 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printfu(va_list ap)
{
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	return (ft_putnbr_base(nb, "0123456789"));
}

int	ft_printfx(va_list ap)
{
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	return (ft_putnbr_base((unsigned long int)nb, "0123456789abcdef"));
}

int	ft_printfmx(va_list ap)
{
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	return (ft_putnbr_base((unsigned long int)nb, "0123456789ABCDEF"));
}

int	ft_printfpourcent(va_list ap)
{
	ap = ap;
	return (ft_putchar('%'));
}
