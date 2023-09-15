/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:39:30 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/15 17:26:18 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_set(t_pge *game)
{
	game->player = set_player(&game->cub->player_pos, game->cub->player_angle,
			M_PI_2);
	if (game->player == NULL)
	{
		cub_clear(game);
		game_clear(game);
		exit(3);
	}
	if (add_texture(game) == 0)
	{
		cub_clear(game);
		game_clear(game);
		exit(4);
	}
	game->cub->map_depth = 100.0f;
	return (0);
}

int	main2(t_pge *game)
{
	cub_set(game);
	look_direction(game, game->cub->player_angle);
	if (game_open_window(game, "Cub3D") == 0)
		return (cub_clear(game), game_clear(game), 2);
	game_loop(game, &cub_launch);
	return (0);
}

int	main(int ac, char **av)
{
	t_pge	*game;
	t_vi	screen;
	t_vi	pxl;

	if (ac < 2)
		return (printf("Usage: %s <file>.cub\n", av[0]), 0);
	screen.x = 1080;
	screen.y = 720;
	pxl.x = 1;
	pxl.y = 1;
	game = game_init(&screen, &pxl);
	if (!game)
		return (1);
	game->cub = init_cub();
	if (!game->cub)
		return (game_clear(game), 1);
	game->portal = init_portal();
	if (!game->portal)
		return (cub_clear(game), game_clear(game), 1);
	if (check_file(game, av[1]))
		return (cub_clear(game), game_clear(game), 1);
	return (main2(game));
}

void	add_laser(t_pge *game, double shift, t_pxl blue_laser, t_pxl orange_laser)
{
	t_vi	coor;
	t_vi	size;
	t_pxl	pixel;

	coor = set_vector((game->drawing_img.width / 2) + shift, game->drawing_img.height / 2);
	size = set_vector(game->drawing_img.width / 7.5, game->drawing_img.height / 4);
	if (game->portal->blue_led == true && game->portal->laserbeam == true)
		pixel = blue_laser;
	else if (game->portal->orange_led == true && game->portal->laserbeam == true)
		pixel = orange_laser;
	else
		pixel = set_pxl_argb(255, 255, 255, 255);
	draw_line(&coor, &size, game, &pixel);
	coor = set_vector((game->drawing_img.width / 2), game->drawing_img.height / 2 + shift);
	size = set_vector(game->drawing_img.width / 7.5, game->drawing_img.height / 4);
	if (game->portal->blue_led == true && game->portal->laserbeam == true)
		pixel = blue_laser;
	else if (game->portal->orange_led == true && game->portal->laserbeam == true)
		pixel = orange_laser;
	else
		pixel = set_pxl_argb(255, 255, 255, 255);
	draw_line(&coor, &size, game, &pixel);
}

void	print_laserbeam(t_pge *game)
{
	t_vi	coor;
	t_vi	size;
	t_pxl	pixel;

	coor = set_vector((game->drawing_img.width / 2), game->drawing_img.height / 2);
	size = set_vector(game->drawing_img.width / 7.5, game->drawing_img.height / 4);
	if (game->portal->blue_led == true && game->portal->laserbeam == true)
		pixel = set_pxl_argb(173, 221, 255, 0);
	else if (game->portal->orange_led == true && game->portal->laserbeam == true)
		pixel = set_pxl_argb(255, 210, 128, 0);
	else
		pixel = set_pxl_argb(255, 255, 255, 255);
	draw_line(&coor, &size, game, &pixel);
	add_laser(game, 1, set_pxl_argb(121, 199, 255, 0), set_pxl_argb(255, 200, 99, 0));
	add_laser(game, 2, set_pxl_argb(80, 181, 255, 0), set_pxl_argb(255, 188, 65, 0));
	add_laser(game, 3, set_pxl_argb(43, 166, 255, 0), set_pxl_argb(255, 178, 38, 0));
	// add_laser(game, 4, set_pxl_argb(0, 148, 255, 0), set_pxl_argb(255, 165, 0, 0));
}

void	print_visor(t_pge *game)
{
	print_crosshair(game);
	print_laserbeam(game);
	print_portal_gun(game);
}

int	cub_launch(void *g)
{
	t_pge	*game;

	game = (t_pge *)g;
	raycast_init(game);
	check_movements(game);
	print_visor(game);
	check_portal(game);
	game_refresh(game);
	return (0);
}
