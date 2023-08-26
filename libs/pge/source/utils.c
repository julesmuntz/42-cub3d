/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:21 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/26 14:57:15 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	get_pixel_from_xpm(t_xpm *xpm, int x, int y, t_pxl *pxl)
{
	unsigned int const	*array = (unsigned int const *)xpm->addr;

	if (x < 0 || x > xpm->width || y < 0 || y > xpm->height)
	{
		*pxl = set_pxl_argb(0, 0, 0, 255);
		return ;
	}
	set_pxl_hex(array[x + xpm->width * y], pxl);
	return ;
}

void	get_pixel_from_img(t_im img, int x, int y, t_pxl *pxl)
{
	unsigned int const	*array = (unsigned int const *)img.addr;

	if (x < 0 || x > img.width || y < 0 || y > img.height)
	{
		set_pxl_hex(0, pxl);
		return ;
	}
	set_pxl_hex(array[x + img.width * y], pxl);
	return ;
}

size_t	ft_xpmlen(t_xpm **xpm)
{
	size_t	i;

	i = 0;
	if (xpm == NULL)
		return (i);
	while (xpm[i])
		i++;
	return (i);
}

t_xpm	**new_xpm_array(t_xpm **xpm)
{
	int		i;
	size_t	size;
	t_xpm	**new;

	size = ft_xpmlen(xpm) + 1;
	new = ft_calloc(sizeof(t_xpm *), (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	if (size == 1)
		return (new);
	while (xpm[i])
	{
		new[i] = xpm[i];
		i++;
	}
	new[i] = NULL;
	new[i + 1] = NULL;
	free(xpm);
	return (new);
}

t_xpm	*find_xpm(t_xpm **array, char *name)
{
	int	i;
	int	len;

	if (!array || !name)
		return (NULL);
	i = 0;
	len = ft_strlen(name);
	while (array[i])
	{
		if ((int)ft_strlen(array[i]->name) == len
				&& ft_strncmp(name, array[i]->name, len) == 0)
			return (array[i]);
		i++;
	}
	return (NULL);
}
