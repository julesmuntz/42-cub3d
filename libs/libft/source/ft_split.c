/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:07:57 by gfranque          #+#    #+#             */
/*   Updated: 2022/09/15 11:25:51 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbwrds(char *s, char c)
{
	int	n[2];

	n[0] = 0;
	n[1] = 0;
	while (s[n[0]])
	{
		if (n[0] > 0 && s[n[0]] == c && s[n[0] - 1] != c)
			n[1]++;
		else if (s[n[0]] != c && !s[n[0] + 1])
			n[1]++;
		n[0]++;
	}
	return (n[1]);
}

static int	ft_lengthword(char *s, char c)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (s[i[0]] && s[i[0]] == c)
		i[0]++;
	while (s[i[0] + i[1]] && s[i[0] + i[1]] != c)
		i[1]++;
	return (i[1]);
}

static int	ft_recurcivemind(char *s, char c, char **strs, int *n)
{
	int	i[2];

	i[0] = 0;
	while (n[0] < n[1] && s[i[0]])
	{
		i[1] = ft_lengthword(s, c);
		if (s[i[0]] != c)
		{
			strs[n[0]] = ft_calloc(i[1] + 1, sizeof(char));
			if (!strs[n[0]])
				return (0);
			ft_strlcpy(strs[n[0]], s + i[0], i[1] + 1);
			n[0]++;
			if (ft_recurcivemind(s + i[0] + i[1] + 1, c, strs, n))
				return (1);
			else
				return (free(strs[n[0]]), 0);
		}
		i[0]++;
	}
	strs[n[0]] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		n[2];
	char	**strs;

	if (!s)
		return (NULL);
	n[0] = 0;
	n[1] = ft_nbwrds((char *)s, c);
	strs = ft_calloc(n[1] + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	if (ft_recurcivemind((char *)s, c, strs, n) == 0)
		return (free(strs), NULL);
	return (strs);
}
/*
int	main(int ac, char **av)
{
	char	**strs;
	int		i;
	
	i = 0;
	ac++;
	strs = ft_split(av[1], 0);
	printf("word lenght [%d]\n", ft_lengthword(av[1], ' '));
	while (strs[i] && i < ft_atoi(av[2]))
	{
		printf("split [%d] [%s]\n", i, strs[i]);
		i++;
	}
	i = 0;
	while (strs[i] && i <= ft_atoi(av[2]))
	{
		free (strs[i]);
		i++;
	}
	free (strs);
	return (0);
}
*/
