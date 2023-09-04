/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:03 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/04 14:28:41 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	draw_rectangle(t_vi *coor, t_vi *v, t_pge *game, t_pxl *pxl)
{
	t_vi	vvrtl;
	t_vi	vhrzt;
	t_vi	p1;
	t_vi	p2;

	if (v->x == 0 || v->y == 0)
		draw_line(coor, v, game, pxl);
	vvrtl = set_vector(0, v->y);
	vhrzt = set_vector(v->x, 0);
	p1 = set_vector(coor->x + v->x, coor->y);
	p2 = set_vector(coor->x, coor->y + v->y);
	draw_line(coor, &vvrtl, game, pxl);
	draw_line(coor, &vhrzt, game, pxl);
	draw_line(&p1, &vvrtl, game, pxl);
	draw_line(&p2, &vhrzt, game, pxl);
	return ;
}

void	fill_rectangle(t_vi *coor, t_vi *v, t_pge *game, t_pxl *pxl)
{
	short int	i;
	short int	y;
	t_vi		vhrzt;

	if (v->x == 0 || v->y == 0)
		return (draw_line(coor, v, game, pxl));
	y = coor->y + v->y;
	i = 1;
	if (y < coor->y)
		i = -1;
	vhrzt = set_vector(v->x, 0);
	while (coor->y != y)
	{
		draw_line(coor, &vhrzt, game, pxl);
		coor->y += i;
	}
	return ;
}
