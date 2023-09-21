/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_ray_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:25:14 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/21 15:12:49 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	collition_in_portal(t_pge *game)
{
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x + 0.1f)] == 'B')
		return ('B');
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x - 0.1f)] == 'B')
		return ('B');
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x - 0.1f)] == 'B')
		return ('B');
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x + 0.1f)] == 'B')
		return ('B');
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x + 0.1f)] == 'O')
		return ('O');
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x - 0.1f)] == 'O')
		return ('O');
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x - 0.1f)] == 'O')
		return ('O');
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x + 0.1f)] == 'O')
		return ('O');
	return ('P');
}

void	teleport_rotation(t_pge *game, char dir)
{
	if (dir == 'N' && game->player->p == 'N')
		look_direction(game, M_PI);
	else if (dir == 'N' && game->player->p == 'E')
		look_direction(game, M_PI_2);
	else if (dir == 'N' && game->player->p == 'W')
		look_direction(game, -M_PI_2);
	else if (dir == 'E' && game->player->p == 'E')
		look_direction(game, M_PI);
	else if (dir == 'E' && game->player->p == 'S')
		look_direction(game, M_PI_2);
	else if (dir == 'E' && game->player->p == 'N')
		look_direction(game, -M_PI_2);
	else if (dir == 'W' && game->player->p == 'W')
		look_direction(game, M_PI);
	else if (dir == 'W' && game->player->p == 'N')
		look_direction(game, M_PI_2);
	else if (dir == 'W' && game->player->p == 'S')
		look_direction(game, -M_PI_2);
	else if (dir == 'S' && game->player->p == 'S')
		look_direction(game, M_PI);
	else if (dir == 'S' && game->player->p == 'W')
		look_direction(game, M_PI_2);
	else if (dir == 'S' && game->player->p == 'E')
		look_direction(game, -M_PI_2);
}

char	check_pos_side(t_pge *game)
{
	if ((int)game->player->oldpos.x < (int)game->player->pos.x)
		game->player->p = 'E';
	else if ((int)game->player->oldpos.x > (int)game->player->pos.x)
		game->player->p = 'W';
	else if ((int)game->player->oldpos.y < (int)game->player->pos.y)
		game->player->p = 'S';
	else if ((int)game->player->oldpos.y > (int)game->player->pos.y)
		game->player->p = 'N';
	return (game->player->p);
}

void	check_portal_2(t_pge *game)
{
	if (game->cub->map[game->player->target.y][game->player->target.x] == '1')
	{
		game->cub->map[game->player->portalo.y][game->player->portalo.x] = '1';
		game->cub->map[game->player->target.y][game->player->target.x] = 'O';
		game->player->portalo = set_vector(game->player->target.x,
				game->player->target.y);
		portal_orientation(game, &game->player->po);
		game->portal->clicked_orange = true;
	}
	game->portal->portal = 0;
}
