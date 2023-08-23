/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:21 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/21 17:10:53 by gfranque         ###   ########.fr       */
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
	printf("xpm dans new array %p\n", xpm);
	free(xpm);
	return (new);
}
/*retourne un void * de la taille du sizeof envoie*/
