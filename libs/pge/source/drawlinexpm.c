/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawlinexpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:08:06 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/30 13:55:56 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	draw_line_xpm(t_vi *coor, t_vi *v, t_xpm *xpm, t_pxl *pxl)
{
	int		i;
	int		step;
	t_vi	xy;
	t_vi	dxy;
	t_vi	inc;

	if (v->x == 0 && v->y == 0)
		return ;
	dxy.x = (coor->x + v->x) - coor->x;
	dxy.y = (coor->x + v->y) - coor->y;
	if (abs(dxy.x) > abs(dxy.y))
		step = abs(dxy.x);
	else
		step = abs(dxy.y);
	inc.x = dxy.x / step;
	inc.y = dxy.y / step;
	xy = copy_vector(&coor);
	i = 1;
	while (i <= step)
	{
		draw_pixel_xpm(&xy, xpm, pxl);
		xy.x = xy.x + inc.x;
		xy.y = xy.y + inc.y;
		i++;
	}
}

void	draw_rectangle_xpm(t_vi *coor, t_vi *v, t_xpm *xpm, t_pxl *pxl)
{
	t_vi	xy;
	t_vi	v1;

	if (v->x == 0 || v->y == 0)
		return ;
	xy = set_vector(coor->x + v->x, coor->y + v->y);
	v1 = set_vector(v->x, 0);
	draw_line_xpm(coor, &v1, xpm, pxl);
	v1 = set_vector(0, v->y);
	draw_line_xpm(coor, &v1, xpm, pxl);
	v1 = set_vector(-v->x, 0);
	draw_line_xpm(&xy, &v1, xpm, pxl);
	v1 = set_vector(0, -v->y);
	draw_line_xpm(&xy, &v1, xpm, pxl);
}

void	fill_rectangle_xpm(t_vi *coor, t_vi *v, t_xpm *xpm, t_pxl *pxl)
{
	int		xf;
	int		step;
	t_vi	xy;
	t_vi	v1;

	if (v->x == 0 || v->y == 0)
		return ;
	xy = copy_vector(coor);
	xf = xy.x + v->x;
	step = 1;
	v1 = set_vector(0, v->y);
	if (v->x < 0)
		step = -1;
	while (xy.x != xf)
	{
		draw_line_xpm(&xy, &v1, xpm, pxl);
		xy.x += step;
	}
}
