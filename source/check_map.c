/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:32:27 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/28 16:42:35 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_space_around(t_pge *game, int a, int b)
{
	if (a - 1 >= 0 && game->cub->map[a - 1][b] == ' ')
		return (true);
	if (a + 1 < game->cub->map_height && game->cub->map[a + 1][b] == ' ')
		return (true);
	if (b - 1 >= 0 && game->cub->map[a][b - 1] == ' ')
		return (true);
	if (game->cub->map[a][b + 1] == ' ')
		return (true);
	return (false);
}

static void	flood_fill(t_pge *game, int a, int b, bool *failure)
{
	if (a < 0 || b < 0 || a >= game->cub->map_height || !game->cub->map[a]
		|| !game->cub->map[a][b])
	{
		*failure = true;
		return ;
	}
	if (game->cub->map[a][b] == '1' || game->cub->map[a][b] == 'X')
		return ;
	game->cub->map[a][b] = 'X';
	flood_fill(game, a + 1, b, failure);
	flood_fill(game, a - 1, b, failure);
	flood_fill(game, a, b + 1, failure);
	flood_fill(game, a, b - 1, failure);
}

int	check_map(t_pge *game, char *arg)
{
	int		b;
	int		a;
	bool	failure;

	failure = false;
	init_map(game, arg);
	if (!game->cub->map)
		return (ft_free_lines(game->cub->map), 1);
	game->cub->map_found = true;
	a = 0;
	while (game->cub->map[a])
	{
		b = 0;
		while (game->cub->map[a][b])
		{
			if (ft_ismap_char(game->cub->map[a][b]) == false)
			{
				failure = true;
				break ;
			}
			if (ft_ismap_player(game->cub->map[a][b]) == true)
			{
				if (game->cub->player_found == true)
				{
					game->cub->multiple_players = true;
					failure = true;
					break ;
				}
				game->cub->player_found = true;
			}
			if ((game->cub->map[a][b] == '0'
				|| ft_ismap_player(game->cub->map[a][b]))
				&& (is_space_around(game, a, b)))
			{
				failure = true;
				break ;
			}
			b++;
		}
		if (failure)
			break ;
		a++;
	}
	if (game->cub->player_found == true && failure == false)
		flood_fill(game, game->cub->player_pos.y,
			game->cub->player_pos.x, &failure);
	a = 0;
	while (game->cub->map[a])
	{
		b = 0;
		while (game->cub->map[a][b])
		{
			if (game->cub->map[a][b] == '1')
				game->cub->wall_found = true;
			if (game->cub->map[a][b] == '0')
				game->cub->unreachable_areas = true;
			b++;
		}
		a++;
	}
	if (failure == false)
		game->cub->valid_map = true;
	return (0);
}
