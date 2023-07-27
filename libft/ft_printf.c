/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:35:22 by gfranque          #+#    #+#             */
/*   Updated: 2022/09/06 12:55:44 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pf	ft_checktype(char c)
{
	t_pf	*tab;

	tab = (t_pf[128]){
		NULL,
	['c'] = &ft_printfc,
	['s'] = &ft_printfs,
	['p'] = &ft_printfp,
	['d'] = &ft_printfd,
	['i'] = &ft_printfi,
	['u'] = &ft_printfu,
	['x'] = &ft_printfx,
	['X'] = &ft_printfmx,
	['%'] = &ft_printfpourcent
	};
	return (tab[(int)c]);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		n;
	t_pf	tmp;
	va_list	ap;

	i = -1;
	n = 0;
	va_start(ap, s);
	if ((s[0] == '%' && s[1] == '\0') || s == NULL)
		return (-1);
	while (s[++i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			tmp = ft_checktype(s[++i]);
			if (tmp)
				n = n + (*tmp)(ap);
			else
				n = n + ft_putchar('%');
		}
		else
			n = n + ft_putchar(s[i]);
	}
	va_end(ap);
	return (n);
}
