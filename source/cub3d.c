/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:39:30 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/24 19:07:26 by julmuntz         ###   ########.fr       */
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
	if (check_file(game, av[1]))
		return (1);
	game->player = set_player(&game->cub->player_pos, game->cub->player_angle, M_PI_2);
	printf("Player position: (x %d) (y %d)\n", game->cub->player_pos.x, game->cub->player_pos.y);
	printf("Player angle:    %f\n", game->cub->player_angle);
	for (int i = 0; game->cub->map[i]; i++)
		write(1, game->cub->map[i], ft_strlen(game->cub->map[i]));
	write(1, "\n", 1);
	game_loop(game);
	return (0);
}
