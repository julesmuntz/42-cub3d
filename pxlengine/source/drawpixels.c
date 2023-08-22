/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:08 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/22 16:45:16 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	draw_strait_line(t_vi const *xy, t_vi const *v, t_pge *game,
			t_pxl *pxl)
{
	t_vi	xyp;
	short int	i;

	xyp = copy_vector(xy);
	if (v->x == 0)
	{
		i = v->y / abs(v->y);
		while (xyp.y != (xy->y + v->y))
		{
			draw_pixel(&xyp, game, &game->drawing_img, pxl);
			xyp.y += i;
		}
	}
	else
	{
		i = v->x / abs(v->x);
		while (xyp.x != (xy->x + v->x))
		{
			draw_pixel(&xyp, game, &game->drawing_img, pxl);
			xyp.x += i;
		}
	}
	return ;
}

void	draw_diagonal(t_vi const *xy, t_vi const *v, t_pge *game,
			t_pxl *pxl)
{
	t_vi	xyp;
	short int	i;
	short int	j;

	xyp = copy_vector(xy);
	i = 1;
	j = 1;
	if (v->x < 0)
		i = -1;
	if (v->y < 0)
		i = -1;
	while (xyp.x != (xy->x + v->x))
	{
		draw_pixel(&xyp, game, &game->drawing_img, pxl);
		xyp.x += i;
		xyp.y += j;
	}
	return ;
}

void	draw_line_x(t_vi xy, t_vi *v, t_pge *game, t_pxl *pxl)
{
	short int		i;
	short int		p;
	short int const	x = xy.x + v->x;

	i = 1;
	if (v->y < 0)
		i = -1;
	p = 2 * abs(v->y) - abs(v->x);
	while (xy.x != x)
	{
		draw_pixel(&xy, game, &game->drawing_img, pxl);
		xy.x ++;
		if (p < 0)
			p = p + 2 * abs(v->y);
		else
		{
			p = p + 2 * abs(v->y) - 2 * abs(v->x);
			xy.y += i;
		}
	}
	return ;
}

void	draw_line_y(t_vi xy, t_vi *v, t_pge *game, t_pxl *pxl)
{
	short int		i;
	short int		p;
	short int const	y = xy.y + v->y;

	i = 1;
	if (v->x < 0)
		i = -1;
	p = 2 * abs(v->x) - abs(v->y);
	while (xy.y != y)
	{
		draw_pixel(&xy, game, &game->drawing_img, pxl);
		xy.y ++;
		if (p < 0)
			p = p + 2 * abs(v->x);
		else
		{
			p = p + 2 * abs(v->x) - 2 * abs(v->y);
			xy.x += i;
		}
	}
	return ;
}

void	draw_line(t_vi *xy, t_vi *v, t_pge *game,
			t_pxl *pxl)
{
	if (v->x == 0 && v->y == 0)
		return ;
	if (v->x == 0 || v->y == 0)
		return (draw_strait_line(xy, v, game, pxl));
	if (abs(v->x) == abs(v->y))
		return (draw_diagonal(xy, v, game, pxl));
	if ((abs(v->x) > abs(v->y) && v->x < 0)
		|| (abs(v->x) < abs(v->y) && v->y < 0))
	{
		xy->x += v->x;
		xy->y += v->y;
		v->x *= -1;
		v->y *= -1;
	}
	if (abs(v->x) > abs(v->y))
		draw_line_x(*xy, v, game, pxl);
	else
		draw_line_y(*xy, v, game, pxl);
	return ;
}
