/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_ray_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:25:14 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/21 16:44:51 by gfranque         ###   ########.fr       */
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
	t_vf	posdif;

	posdif = set_vectorf(game->player->pos.x - game->player->oldpos.x,
			game->player->pos.y - game->player->oldpos.y);
	if (fabs(posdif.x) > fabs(posdif.y))
	{
		if (posdif.x > 0)
			game->player->p = 'E';
		else
			game->player->p = 'W';
	}
	else if (fabs(posdif.x) < fabs(posdif.y))
	{
		if (posdif.y > 0)
			game->player->p = 'S';
		else
			game->player->p = 'N';
	}
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

int	is_in_the_right_place(t_pge *game, t_vi *portal, char side)
{
	if (side == 'E' && portal->x -1 == (int)game->player->pos.x
		&& portal->y == (int)game->player->pos.y)
		return (1);
	else if (side == 'W' && portal->x + 1 == (int)game->player->pos.x
		&& portal->y == (int)game->player->pos.y)
		return (1);
	else if (side == 'N' && portal->x == (int)game->player->pos.x
		&& portal->y + 1 == (int)game->player->pos.y)
		return (1);
	else if (side == 'S' && portal->x == (int)game->player->pos.x
		&& portal->y - 1 == (int)game->player->pos.y)
		return (1);
	return (0);
}
