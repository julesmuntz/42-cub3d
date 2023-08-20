/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:39:58 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/20 17:42:05 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_interpolation(float color1, float color2, float dist)
{
	int	color3;

	if (dist >= g_map_depth)
		return (color2);
	color3 = (int)(color1 * ((g_map_depth - dist) / (g_map_depth - 0.1f))
			+ color2 * ((dist - 0.1f) / (g_map_depth - 0.1f)));
	return (color3);
}

int	color_interpolation_rgb(int color1, int color2, float dist)
{
	int	colorrgb1[3];
	int	colorrgb2[3];
	int	colorrgb3[3];

	colorrgb1[2] = color1 % 256;
	color1 = color1 / 256;
	colorrgb1[1] = color1 % 256;
	color1 = color1 / 256;
	colorrgb1[0] = color1 % 256;
	colorrgb2[2] = color2 % 256;
	color1 = color1 / 256;
	colorrgb2[1] = color2 % 256;
	color1 = color1 / 256;
	colorrgb2[0] = color2 % 256;
	colorrgb3[0] = color_interpolation(colorrgb1[0], colorrgb2[0], dist);
	colorrgb3[1] = color_interpolation(colorrgb1[1], colorrgb2[1], dist);
	colorrgb3[2] = color_interpolation(colorrgb1[2], colorrgb2[2], dist);
	return (colorrgb3[0] * 65536 + colorrgb3[1] * 256 + colorrgb3[2]);
}
