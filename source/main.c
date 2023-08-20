/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:23:05 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/20 17:36:37 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**g_map = NULL;
float	g_player_x = 0.0f;
float	g_player_y = 0.0f;
float	g_player_a = 0.0f;
int		g_screen_width = 1080;
int		g_screen_height = 720;
float	g_fov = PI / 4;
float	g_map_depth = 0.0f;
bool	g_gofront = false;
bool	g_goback = false;
bool	g_goleft = false;
bool	g_goright = false;
bool	g_lookleft = false;
bool	g_lookright = false;
int		g_pixels = 0;
char	*g_file_path = NULL;

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_config	config;

	if (ac < 2)
		return (printf("Usage: %s <file>.cub\n", av[0]), 0);
	g_file_path = av[1];
	init_map(g_file_path);
	mlx.ptr_mlx = mlx_init();
	mlx.ptr_window = mlx_new_window(mlx.ptr_mlx, g_screen_width,
			g_screen_height, "cub");
	mlx.img.mlx_img = mlx_new_image(mlx.ptr_mlx, g_screen_width,
			g_screen_height);
	mlx.img.addr = mlx_get_data_addr(mlx.img.mlx_img, &mlx.img.bpp,
			&mlx.img.line_len, &mlx.img.endian);
	init_textures(&mlx, &config, g_file_path);
	set_texture_to_walls(config.north_texture, &mlx, &config);
	// set_texture_to_walls(config.south_texture, &mlx, &config);
	// set_texture_to_walls(config.west_texture, &mlx, &config);
	// set_texture_to_walls(config.east_texture, &mlx, &config);
	mlx.wall.addr = mlx_get_data_addr(mlx.wall.mlx_img, &mlx.wall.bpp,
			&mlx.wall.line_len, &mlx.wall.endian);
	trace_into_image(&mlx, g_map);
	mlx_put_image_to_window(mlx.ptr_mlx, mlx.ptr_window, mlx.img.mlx_img, 0, 0);
	mlx_loop_hook(mlx.ptr_mlx, &ft_loop, &mlx);
	mlx_hook(mlx.ptr_window, KeyPress, KeyPressMask, &ft_key_press, &mlx);
	mlx_hook(mlx.ptr_window, KeyRelease, KeyReleaseMask, &ft_key_release, &mlx);
	mlx_loop(mlx.ptr_mlx);
	mlx_destroy_display(mlx.ptr_mlx);
	ft_free_lines(g_map);
	free(mlx.ptr_mlx);
	return (0);
}

/*
int	to_fx(float n)
{
	return (n * (1 << 8));
}

int	mul_fx(float a, float b)
{
	int	c;
	int	d;

	c = a * (1 << 8);
	d = b * (1 << 8);
	return (c * d >> 8);
}

int	div_fx(float a, float b)
{
	int	c;
	int	d;

	c = a * (1 << 8);
	d = b * (1 << 8);
	if (d == 0)
		return (0);
	return ((c << 8) / d);
}
*/
