/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:32:27 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/04 17:44:26 by julmuntz         ###   ########.fr       */
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

static bool	check_map_characters(t_pge *game, int *a, int *b, bool *failure)
{
	while (game->cub->map[*a])
	{
		*b = 0;
		while (game->cub->map[*a][*b])
		{
			if (ft_ismap_char(game->cub->map[*a][*b]) == false)
			{
				*failure = true;
				return (true);
			}
			if (ft_ismap_player(game->cub->map[*a][*b]) == true)
			{
				if (game->cub->player_found == true)
				{
					game->cub->multiple_players = true;
					*failure = true;
					return (true);
				}
				game->cub->player_found = true;
			}
			(*b)++;
		}
		(*a)++;
	}
	return (false);
}

static bool	is_space_around_and_flood_fill(t_pge *game,
	int *a, int *b, bool *failure)
{
	*a = 0;
	while (game->cub->map[*a])
	{
		*b = 0;
		while (game->cub->map[*a][*b])
		{
			if ((game->cub->map[*a][*b] == '0'
				|| ft_ismap_player(game->cub->map[*a][*b]))
				&& (is_space_around(game, *a, *b)))
			{
				*failure = true;
				return (true);
			}
			(*b)++;
		}
		(*a)++;
	}
	if (game->cub->player_found == true && *failure == false)
		flood_fill(game, game->cub->player_pos.y, game->cub->player_pos.x,
			failure);
	return (false);
}

static void	check_walls_and_unreachable_areas(t_pge *game)
{
	int	a;
	int	b;

	a = 0;
	while (game->cub->map[a])
	{
		b = 0;
		while (game->cub->map[a][b])
		{
			if (game->cub->map[a][b] == '1')
			{
				game->cub->wall_found = true;
				return ;
			}
			if (game->cub->map[a][b] == '0')
				game->cub->unreachable_areas = true;
			b++;
		}
		a++;
	}
}

int	check_map(t_pge *game, char *arg)
{
	bool	failure;
	int		a;
	int		b;

	failure = false;
	init_map(game, arg);
	if (!game->cub->map)
		return (ft_free_lines(game->cub->map), 1);
	game->cub->map_found = true;
	a = 0;
	if (check_map_characters(game, &a, &b, &failure))
		return (0);
	if (is_space_around_and_flood_fill(game, &a, &b, &failure))
		return (0);
	check_walls_and_unreachable_areas(game);
	if (failure == false)
		game->cub->valid_map = true;
	return (0);
}
