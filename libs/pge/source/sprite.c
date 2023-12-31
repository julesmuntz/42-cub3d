/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:09 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/19 18:07:42 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	print_sprite_vector_set(t_vi *xy, t_vi *coor, t_vi *p)
{
	xy->x += p->x;
	xy->y = coor->y;
}

void	print_sprite(t_xpm *xpm, t_vi coor, t_vi v, t_xpm *img)
{
	t_vi	xy;
	t_vi	p;
	t_pxl	pxl;

	if (!xpm)
		return ;
	set_pxl_hex(0, &pxl);
	p = set_vector(1, 1);
	if (v.x < 0)
		p.x = -1;
	if (v.y < 0)
		p.y = -1;
	xy = set_vector(coor.x, coor.y);
	while (xy.x != coor.x + v.x)
	{
		while (xy.y != coor.y + v.y)
		{
			get_pixel_from_xpm(xpm, ((float)(xy.x - coor.x)) / (float)v.x
				* (float)xpm->width, ((float)(xy.y - coor.y)) / (float)v.y
				* (float)xpm->height, &pxl);
			draw_pixel(&xy, img, &pxl);
			xy.y += p.y;
		}
		print_sprite_vector_set(&xy, &coor, &p);
	}
}

int	new_sprite(t_vi const *size, char const *name, t_xpm **xpm, t_pge *game)
{
	int		len;
	t_vi	coor;
	t_pxl	pxl;

	if (!size || !name)
		return (0);
	len = ft_xpmlen(xpm);
	xpm[len] = malloc(sizeof(t_xpm) * 1);
	if (!xpm[len])
		return (0);
	xpm[len]->img = mlx_new_image(game->ptr_mlx, size->x, size->y);
	if (!xpm[len]->img)
		return (0);
	xpm[len]->width = size->x;
	xpm[len]->height = size->y;
	xpm[len]->addr = mlx_get_data_addr(xpm[len]->img, &xpm[len]->bpp,
			&xpm[len]->line_len, &xpm[len]->endian);
	xpm[len]->name = (char *)name;
	coor = set_vector(0, 0);
	pxl = set_pxl_argb(0, 0, 0, 255);
	fill_rectangle_xpm(&coor, size, xpm[len], &pxl);
	return (1);
}

t_xpm	**game_add_sprite(t_vi const *size, char const *name, t_xpm **xpm,
		t_pge *game)
{
	xpm = new_xpm_array(xpm);
	if (xpm == NULL)
		return (NULL);
	if (new_sprite(size, name, xpm, game) == 0)
		return (free_xpm(xpm, game), NULL);
	if (check_xpm(xpm) == 0)
		return (free_xpm(xpm, game), NULL);
	return (xpm);
}
