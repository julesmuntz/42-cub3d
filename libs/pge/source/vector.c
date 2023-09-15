/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:27 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/15 17:48:19 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

t_vi	set_vector(short int const x, short int const y)
{
	t_vi	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vi	set_vector_by_points(t_vi const *a, t_vi const *b)
{
	t_vi	v;

	v.x = b->x - a->x;
	v.y = b->y - a->y;
	return (v);
}

short int	compare_vector(t_vi const *a, t_vi const *b)
{
	if (a->x == b->x && a->y == b->y)
		return (1);
	return (0);
}

t_vi	copy_vector(t_vi const *a)
{
	t_vi	v;

	v.x = a->x;
	v.y = a->y;
	return (v);
}

void	vector_rotation(t_vi *v, float angle)
{
	t_vi	w;

	w.x = v->x * cosf(angle) - v->y * sinf(angle);
	w.y = v->x * sin(angle) + v->y * cosf(angle);
	v->x = w.x;
	v->y = w.y;
}
