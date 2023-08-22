/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:09 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/22 16:45:31 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	print_sprite(t_xpm *xpm, t_vi coor, t_vi v, t_pge *game)
{
	t_vi	xy;
	t_vi	p;
	t_pxl		pxl;

	set_pxl_hex(0, &pxl);
	p = set_vector(1, 1);
	if (v.x < 0)
		p.x = -1;
	if (v.y < 0)
		p.y = -1;
	xy.x = coor.x;
	while (xy.x != coor.x + v.x)
	{
		xy.y = coor.y;
		while (xy.y != coor.y + v.y)
		{
			get_pixel_from_xpm(xpm, ((float)(xy.x - coor.x)) / (float)v.x
				* (float)xpm->width, ((float)(xy.y - coor.y)) / (float)v.y
				* (float)xpm->height, &pxl);
			draw_pixel(&xy, game, &game->drawing_img, &pxl);
			xy.y += p.y;
		}
		xy.x += p.x;
	}
}
