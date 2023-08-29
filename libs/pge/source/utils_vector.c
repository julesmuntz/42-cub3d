/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:36 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/29 17:41:35 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

float	vector_dist(t_vi const *v)
{
	return (sqrtf((v->x * v->x) + (v->y * v->y)));
}

float	vectorf_dist(t_vf const *v)
{
	return (sqrtf((v->x * v->x) + (v->y * v->y)));
}
