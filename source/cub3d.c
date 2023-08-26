/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:39:30 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/26 18:22:52 by gfranque         ###   ########.fr       */
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
	pxl.x = 1;
	pxl.y = 1;
	game = game_init(&screen, &pxl, "Cub3D");
	if (!game)
		return (1);
	game->cub = init_cub();
	if (!game->cub)
		return (1);
	if (check_file(game, av[1]))
		return (1);
	game->player = set_player(&game->cub->player_pos, game->cub->player_angle, M_PI_4);
	// printf("Player position: (x %d) (y %d)\n", game->cub->player_pos.x, game->cub->player_pos.y);
	// printf("Player angle:    %f\n", game->cub->player_angle);
	if (add_texture(game) == 0)
	{
		cub_clear(game);
		game_clear(game);
		return (3);
	}
	for (int i = 0; game->cub->map[i]; i++)
		printf("%s\n", game->cub->map[i]);
	printf("player x %f player y %f\n", game->player->pos.x, game->player->pos.y);
	printf("map width %d map height %d\n", game->cub->map_width, game->cub->map_height);
	game_loop(game, &cub_launch);
	return (0);
}

int	cub_launch(void *g)
{
	t_pge	*game;

	game = (t_pge *)g;
	raycast_init(game);
	check_movements(game);
	game_refresh(game);
	return (0);
}
