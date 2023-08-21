/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:27 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/21 16:37:29 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

t_vector	set_vector(short int const x, short int const y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vector	set_vector_by_points(t_vector const *a, t_vector const *b)
{
	t_vector	v;

	v.x = b->x - a->x;
	v.y = b->y - a->y;
	return (v);
}

short int	compare_vector(t_vector const *a, t_vector const *b)
{
	if (a->x == b->x && a->y == b->y)
		return (1);
	return (0);
}

t_vector	copy_vector(t_vector const *a)
{
	t_vector	v;

	v.x = a->x;
	v.y = a->y;
	return (v);
}
