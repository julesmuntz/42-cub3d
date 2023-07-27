/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:25:47 by gfranque          #+#    #+#             */
/*   Updated: 2022/05/22 13:38:26 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numbsize(long int nb)
{
	int	size;

	size = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

static char	*ft_supermem(int size, int sign)
{
	char	*str;

	str = ft_calloc(size + sign + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

static void	ft_putntr(char *str, long int n, int size, int sign)
{
	int	i;

	i = size + sign - 1;
	while (n > 9)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	str[i] = n + '0';
	if (sign == 1)
		str[0] = '-';
	return ;
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			size;
	int			sign;
	char		*str;

	nb = (long int)n;
	if (nb < 0)
	{
		nb = nb * -1;
		sign = 1;
	}
	else
		sign = 0;
	size = ft_numbsize(nb);
	str = ft_supermem(size, sign);
	ft_putntr(str, nb, size, sign);
	return (str);
}
