/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:15 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/21 17:09:19 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

void	draw_triangle_seg(t_vector const *x, t_vector const *y, t_pge *game,
	t_pxl *pxl)
{
	t_vector	a;
	t_vector	v;

	v = set_vector_by_points(x, y);
	a = copy_vector(x);
	draw_line(&a, &v, game, pxl);
	return ;
}

short int	draw_triangle(t_triangle *t, t_pge *game, t_pxl *pxl)
{
	if (compare_vector(t->x, t->y) == 1 || compare_vector(t->y, t->z) == 1
		|| compare_vector(t->z, t->x) == 1)
		return (0);
	draw_triangle_seg(t->x, t->y, game, pxl);
	draw_triangle_seg(t->y, t->z, game, pxl);
	draw_triangle_seg(t->z, t->x, game, pxl);
	return (1);
}

void	fill_triangle(t_triangle *t, t_pge *game, t_pxl *pxl)
{
	(void)t;
	(void)game;
	(void)pxl;
}
