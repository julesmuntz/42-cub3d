/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:09:13 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/23 16:10:45 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

t_vf	set_vectorf(float const x, float const y)
{
	t_vf	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vf	set_vectorf_by_points(t_vf const *a, t_vf const *b)
{
	t_vf	v;

	v.x = b->x - a->x;
	v.y = b->y - a->y;
	return (v);
}

short int	compare_vectorf(t_vf const *a, t_vf const *b)
{
	if (a->x == b->x && a->y == b->y)
		return (1);
	return (0);
}

t_vf	copy_vectorf(t_vf const *a)
{
	t_vf	v;

	v.x = a->x;
	v.y = a->y;
	return (v);
}

void	vectorf_rotation(t_vf *v, float angle)
{
	t_vf	w;

	w.x = v->x * cosf(angle) - v->y * sinf(angle);
	w.y = v->x * sin(angle) + v->y * cosf(angle);
	v->x = w.x;
	v->y = w.y;
}
