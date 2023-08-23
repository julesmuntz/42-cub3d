/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:02 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/22 16:45:31 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	draw_symetric(t_vi *xy, t_vi *xyp, t_pge *game, t_pxl *pxl)
{
	t_vi	v;

	v = set_vector(xyp->x + xy->x, xyp->y + xy->y);
	draw_pixel(&v, game, &game->drawing_img, pxl);
	v = set_vector(xyp->y + xy->x, xyp->x + xy->y);
	draw_pixel(&v, game, &game->drawing_img, pxl);
	v = set_vector(-xyp->x + xy->x, xyp->y + xy->y);
	draw_pixel(&v, game, &game->drawing_img, pxl);
	v = set_vector(-xyp->y + xy->x, xyp->x + xy->y);
	draw_pixel(&v, game, &game->drawing_img, pxl);
	v = set_vector(xyp->x + xy->x, -xyp->y + xy->y);
	draw_pixel(&v, game, &game->drawing_img, pxl);
	v = set_vector(xyp->y + xy->x, -xyp->x + xy->y);
	draw_pixel(&v, game, &game->drawing_img, pxl);
	v = set_vector(-xyp->x + xy->x, -xyp->y + xy->y);
	draw_pixel(&v, game, &game->drawing_img, pxl);
	v = set_vector(-xyp->y + xy->x, -xyp->x + xy->y);
	draw_pixel(&v, game, &game->drawing_img, pxl);
}

void	draw_circle(t_vi *xy, short int const radius, t_pge *game,
	t_pxl *pxl)
{
	t_vi	xyp;
	int			m;

	xyp.x = 0;
	xyp.y = radius;
	m = 5 - 4 * radius;
	while (xyp.x <= xyp.y)
	{
		draw_symetric(xy, &xyp, game, pxl);
		if (m > 0)
		{
			xyp.y = xyp.y - 1;
			m = m - 8 * xyp.y;
		}
		xyp.x++;
		m = m + 8 * xyp.x + 4;
	}
}
