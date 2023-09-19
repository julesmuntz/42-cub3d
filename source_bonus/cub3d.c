/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:39:30 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/19 18:36:09 by gfranque         ###   ########.fr       */
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
	if (game_open_window(game, "Portal 3D") == 0)
		return (cub_clear(game), game_clear(game), 2);
	t_vi size = set_vector(400, 400);
	game->xpm = game_add_sprite(&size, "bob", game->xpm, game);
	game->xpm = game_add_sprite(&size, "bob1", game->xpm, game);
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

void	print_elements(t_pge *game)
{
	print_crosshair(game);
	print_laserbeam(game);
	print_portal_gun(game);
}

int	cub_launch(void *g)
{
	t_pge	*game;

	game = (t_pge *)g;
	raycast_init(game, set_vectorf(game->player->pos.x,
			game->player->pos.y), &game->drawing_img);
	check_movements(game);
	print_elements(game);
	check_portal(game);
	game_refresh(game);
	return (0);
}
