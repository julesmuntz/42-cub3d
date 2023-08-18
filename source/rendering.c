/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:45:43 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/19 13:51:22 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_im *img, int x, int y, long color)
{
	int *const pixel = (int *)img->addr;
	if (x >= g_screen_width || x < 0 || y >= g_screen_height || y < 0)
		return ;
	pixel[y * g_screen_width + x] = color;
}

float	side_ray(float distance_to_wall, float eye_x, float eye_y)
{
	int	x;
	int	y;

	x = (int)(g_player_x + eye_x * (distance_to_wall - 0.01f));
	y = (int)(g_player_y + eye_y * (distance_to_wall - 0.01f));
	if (x != ((int)(g_player_x + eye_x * distance_to_wall)))
	{
		if (x < ((int)(g_player_x + eye_x * distance_to_wall)))
			return (1.0f - ((g_player_y + eye_y * distance_to_wall)
					- (int)(g_player_y + eye_y * distance_to_wall)));
		else
			return ((g_player_y + eye_y * distance_to_wall) - (int)(g_player_y
					+ eye_y * distance_to_wall));
	}
	if (y < ((int)(g_player_y + eye_y * distance_to_wall)))
		return ((g_player_x + eye_x * distance_to_wall) - (int)(g_player_x
				+ eye_x * distance_to_wall));
	return (1.0f - ((g_player_x + eye_x * distance_to_wall) - (int)(g_player_x
				+ eye_x * distance_to_wall)));
}

int	trace_into_image(t_mlx *mlx, char **g_map)
{
	float		rayangle;
	float		distance_to_wall;
	float		eye_x;
	float		eye_y;
	int			testX;
	int			testY;
	int			ceiling;
	int			floor;
	float		texturevalue;
	float		b;
	bool		hit_wall;
	t_config	config;

	init_colors(&config, g_file_path);
	for (int x = g_pixels; x < g_screen_width; x += 2)
	{
		rayangle = (g_player_a - g_fov / 2) + ((float)x / (float)g_screen_width)
			* g_fov;
		distance_to_wall = 0.0f;
		hit_wall = false;
		eye_x = sinf(rayangle);
		eye_y = cosf(rayangle);
		while (hit_wall == false)
		{
			distance_to_wall += 0.01f;
			testX = (int)(g_player_x + eye_x * distance_to_wall);
			testY = (int)(g_player_y + eye_y * distance_to_wall);
			if (testX < 0 || testX >= g_map_depth || testY < 0
				|| testY >= g_map_depth)
			{
				hit_wall = true;
				distance_to_wall = g_map_depth;
			}
			else
			{
				if (g_map[testY][testX] == '1')
					hit_wall = true;
			}
		}
		ceiling = (float)(g_screen_height / 2.0) - g_screen_height
			/ ((float)distance_to_wall);
		floor = g_screen_height - ceiling;
		texturevalue = side_ray(distance_to_wall, eye_x, eye_y);
		for (int y = 0; y < g_screen_height; y++)
		{
			if (y < ceiling)
			{
				b = 1.0f - (y - g_screen_height / 2.0f) / (g_screen_height
						/ 2.0f);
				img_pix_put(&mlx->img, x, y,
						color_interpolation_rgb(rgb_to_hex(config.ceiling_color),
							0x000000, (b / 3.0f) * g_map_depth));
			}
			else if (y <= floor)
				img_pix_put(&mlx->img, x, y,
						color_interpolation_rgb(xpm_color(mlx, texturevalue,
								(float)(y - ceiling) / (float)(floor
									- ceiling)), 0x000000, distance_to_wall));
			else
			{
				b = 1.0f - (y - g_screen_height / 2.0f) / (g_screen_height
						/ 2.0f);
				img_pix_put(&mlx->img, x, y,
						color_interpolation_rgb(rgb_to_hex(config.floor_color),
							0x000000, b * g_map_depth));
			}
		}
	}
	free(config.ceiling_color);
	free(config.floor_color);
	if (g_pixels == 0)
		g_pixels = 1;
	else
		g_pixels = 0;
	return (0);
}
