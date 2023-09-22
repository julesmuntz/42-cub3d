/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:43:12 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/21 17:20:22 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_direction(t_pge *game, float n)
{
	game->player->angle -= n;
	vectorf_rotation(&game->player->dir, n);
	vectorf_rotation(&game->player->plan, n);
}

static int	teleport_to_orange(t_pge *game)
{
	if (game->player->po == 'S' && game->player->p == 'S')
		game->player->pos = set_vectorf(game->player->portalo.x + 0.5f,
			game->player->portalo.y - 0.5f);
	else if (game->player->po == 'N' && game->player->p == 'N')
		game->player->pos = set_vectorf(game->player->portalo.x + 0.5f,
			game->player->portalo.y + 1.5f);
	else if (game->player->po == 'W' && game->player->p == 'W')
		game->player->pos = set_vectorf(game->player->portalo.x + 1.5f,
			game->player->portalo.y + 0.5f);
	else if (game->player->po == 'E' && game->player->p == 'E')
		game->player->pos = set_vectorf(game->player->portalo.x - 0.5f,
			game->player->portalo.y + 0.5f);
	else
		game->player->pos = game->player->oldpos;
	if (game->player->pos.x != game->player->oldpos.x
			&& game->player->pos.y != game->player->oldpos.y)
		teleport_rotation(game, game->player->po);
	return (0);
}

static int	teleport_to_blue(t_pge *game)
{
	if (game->player->pb == 'S' && game->player->p == 'S')
		game->player->pos = set_vectorf(game->player->portalb.x + 0.5f,
			game->player->portalb.y - 0.5f);
	else if (game->player->pb == 'N' && game->player->p == 'N')
		game->player->pos = set_vectorf(game->player->portalb.x + 0.5f,
			game->player->portalb.y + 1.5f);
	else if (game->player->pb == 'W' && game->player->p == 'W')
		game->player->pos = set_vectorf(game->player->portalb.x + 1.5f,
			game->player->portalb.y + 0.5f);
	else if (game->player->pb == 'E' && game->player->p == 'E')
		game->player->pos = set_vectorf(game->player->portalb.x - 0.5f,
			game->player->portalb.y + 0.5f);
	else
		game->player->pos = game->player->oldpos;
	if (game->player->pos.x != game->player->oldpos.x
			&& game->player->pos.y != game->player->oldpos.y)
		teleport_rotation(game, game->player->pb);
	return (0);
}

static int	is_wall(char c, t_pge *game)
{
	if (game->portal->clicked_blue
		&& game->portal->clicked_orange)
	{
			if (c == '1')
				return (0);
	}
	else if (c == 'B' || c == 'O' || c == '1')
		return (0);
	return (1);
}

bool	check_collision(t_pge *game)
{
	if (game->portal->clicked_blue == true
		&& game->portal->clicked_orange == true)
	{
		if (collition_in_portal(game) == 'B')
			return (teleport_to_orange(game));
		if (collition_in_portal(game) == 'O')
			return (teleport_to_blue(game));
	}
	if (is_wall(game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x + 0.1f)], game) == 0)
		game->player->pos = game->player->oldpos;
	if (is_wall(game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x - 0.1f)], game) == 0)
		game->player->pos = game->player->oldpos;
	if (is_wall(game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x - 0.1f)], game) == 0)
		game->player->pos = game->player->oldpos;
	if (is_wall(game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x + 0.1f)], game) == 0)
		game->player->pos = game->player->oldpos;
	check_pos_side(game);
	// printf("direction of the player [%c]\n", check_pos_side(game));
	// printf("direction of the portalo [%c]\n", game->player->po);
	// printf("direction of the portalb [%c]\n", game->player->pb);
	game->player->oldpos = game->player->pos;
	return (1);
}
