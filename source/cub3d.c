/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:39:30 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/01 17:09:13 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_pge	*game;
	t_vi	screen;
	t_vi	pxl;

	if (ac < 2)
		return (printf("Usage: %s <file>.cub\n", av[0]), 0);
	screen.x = 1080;
	screen.y = 720;
	pxl.x = 2;
	pxl.y = 2;
	game = game_init(&screen, &pxl, "Cub3D");
	if (!game)
		return (1);
	game->cub = init_cub();
	if (!game->cub)
		return (1);
	if (check_file(game, av[1]))
		return (cub_clear(game), game_clear(game), 1);
	game->player = set_player(&game->cub->player_pos, game->cub->player_angle,
		M_PI_2);
	if (add_texture(game) == 0)
		return (cub_clear(game), game_clear(game), 3);
	game->cub->map_depth = 30.0f;
	look_direction(game, game->cub->player_angle);
	game_loop(game, &cub_launch);
	return (0);
}

void	print_visor(t_pge *game)
{
	t_vi	coor;
	t_vi	size;

	// t_pxl	pxl;
	coor = set_vector(game->drawing_img.width / 2, game->drawing_img.height
		/ 2);
	size = copy_vector(&coor);
	print_sprite(find_xpm(game->xpm, "gun"), coor, size, game);
	coor = set_vector(game->drawing_img.width / 2 - 16, game->drawing_img.height / 2 - 16);
	size = set_vector(32 , 32);
	print_sprite(find_xpm(game->xpm, "crosshair"), coor, size, game);
	// coor = set_vector(game->drawing_img.width / 2 - 1,
		// game->drawing_img.height / 2 - 1);
	// pxl = set_pxl_argb(255, 183, 26, 0);
	// draw_circle(&coor, 6, game, &pxl);
	// draw_circle(&coor, 7, game, &pxl);
	// coor = set_vector(game->drawing_img.width / 2 + 1,
		// game->drawing_img.height / 2 + 1);
	// pxl = set_pxl_argb(53, 162, 253, 0);
	// draw_circle(&coor, 6, game, &pxl);
	// draw_circle(&coor, 7, game, &pxl);
	// pxl = set_pxl_argb(255, 255, 255, 0);
	// coor = set_vector(game->drawing_img.width / 2 + 2,
		// game->drawing_img.height / 2);
	// draw_pixel(&coor, game, &game->drawing_img, &pxl);
	// coor = set_vector(game->drawing_img.width / 2 - 2,
		// game->drawing_img.height / 2);
	// draw_pixel(&coor, game, &game->drawing_img, &pxl);
	// coor = set_vector(game->drawing_img.width / 2, game->drawing_img.height
	//	/ 2 + 2);
	// draw_pixel(&coor, game, &game->drawing_img, &pxl);
	// coor = set_vector(game->drawing_img.width / 2, game->drawing_img.height
	//	/ 2 - 2);
	// draw_pixel(&coor, game, &game->drawing_img, &pxl);
	// coor = set_vector(game->drawing_img.width / 2, game->drawing_img.height
	//	/ 2);
	// draw_pixel(&coor, game, &game->drawing_img, &pxl);
}

int	cub_launch(void *g)
{
	t_pge	*game;

	game = (t_pge *)g;
	raycast_init(game);
	check_movements(game);
	print_visor(game);
	game_refresh(game);
	return (0);
}
