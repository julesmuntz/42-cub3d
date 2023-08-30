/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawcirclexpm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:56:07 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/30 14:12:29 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	draw_circle_points(t_vi *coor, t_vi *xy, t_xpm *xpm, t_pxl *pxl)
{
	t_vi	point;

	point = set_vector(coor->x + xy->x, coor->y + xy->y);
	draw_pixel_xpm(&point, xpm, pxl);
	point = set_vector(coor->x + xy->y, coor->y + xy->x);
	draw_pixel_xpm(&point, xpm, pxl);
	point = set_vector(coor->x - xy->x, coor->y + xy->y);
	draw_pixel_xpm(&point, xpm, pxl);
	point = set_vector(coor->x - xy->y, coor->y + xy->x);
	draw_pixel_xpm(&point, xpm, pxl);
	point = set_vector(coor->x + xy->x, coor->y - xy->y);
	draw_pixel_xpm(&point, xpm, pxl);
	point = set_vector(coor->x + xy->y, coor->y - xy->x);
	draw_pixel_xpm(&point, xpm, pxl);
	point = set_vector(coor->x - xy->x, coor->y - xy->y);
	draw_pixel_xpm(&point, xpm, pxl);
	point = set_vector(coor->x - xy->y, coor->y - xy->x);
	draw_pixel_xpm(&point, xpm, pxl);
}

void	draw_circle_xpm(t_vi *coor, int	r, t_xpm *xpm, t_pxl *pxl)
{
	int		d;
	t_vi	xy;

	xy = set_vector(0, r);
	d = r - 1;
	while (xy.y >= xy.x)
	{
		draw_circle_points(coor, &xy, xpm, pxl);
		if (d >= (2 * xy.x))
		{
			d = d - (2 * xy.x) - 1;
			xy.x++;
		}
		else if (d < (2 * (r - xy.y)))
		{
			d = d + (2 * xy.y) - 1;
			xy.y--;
		}
		else
		{
			d = d + (2 * (xy.y - xy.x - 1));
			xy.y--;
			xy.x++;
		}
	}
}

void	fill_circle_xpm(t_vi *coor, int	r, t_xpm *xpm, t_pxl *pxl)
{
	while (r > 0)
	{
		draw_circle_xpm(coor, r, xpm, pxl);
		r--;
	}
}
