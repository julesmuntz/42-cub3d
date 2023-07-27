/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:03:07 by gfranque          #+#    #+#             */
/*   Updated: 2022/05/24 13:26:12 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkinset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_checkfront(char *str, char *set)
{
	int	i;

	i = 0;
	while (ft_checkinset(str[i], set))
		i++;
	return (i);
}

static int	ft_checkback(char *str, char *set)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
		i++;
	i--;
	while (ft_checkinset(str[i], set))
	{
		c++;
		i--;
	}
	return (c);
}

static void	ft_ultimatecpy(char *str, char *s1, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	return ;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	int		dif;
	char	*str;
	char	*s;
	char	*charset;

	s = (char *)s1;
	charset = (char *)set;
	dif = ft_checkfront(s, charset) + ft_checkback(s, charset);
	size = (int)ft_strlen((char *)s1) - dif;
	if (size < 0)
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
		return (str);
	}
	str = ft_calloc((size + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_ultimatecpy(str, s + ft_checkfront(s, charset), size);
	return (str);
}
