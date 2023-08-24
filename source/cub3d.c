/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:39:30 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/24 15:13:16 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub *init_cub(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->north_texture = NULL;
	cub->south_texture = NULL;
	cub->west_texture = NULL;
	cub->east_texture = NULL;
	cub->floor_color = NULL;
	cub->ceiling_color = NULL;
	cub->north_found = false;
	cub->south_found = false;
	cub->west_found = false;
	cub->east_found = false;
	cub->ceiling_found = false;
	cub->floor_found = false;
	cub->map_found = false;
	cub->map_depth = 0.0f;
	cub->player_pos.x = 0;
	cub->player_pos.y = 0;
	cub->player_angle = 0.0f;
	return (cub);
}

int	main(int ac, char **av)
{
	t_pge	*game;
	t_vi	screen;
	t_vi	pxl;

	(void)ac;
	(void)av;
	screen.x = 720;
	screen.y = 480;
	pxl.x = 1;
	pxl.y = 1;
	game = game_init(&screen, &pxl, "Cub3D");
	if (!game)
		return (1);
	game->cub = init_cub();
	if (!game->cub)
		return (1);
	init_map(game, av[1]);
	game->player = set_player(&game->cub->player_pos, game->cub->player_angle, M_PI_2);
	printf("Player position: %d %d\n", game->cub->player_pos.x, game->cub->player_pos.y);
	printf("Player angle: %f\n", game->cub->player_angle);
	game_loop(game);
	return (0);
}
