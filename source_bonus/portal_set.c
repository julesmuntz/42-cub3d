/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:48:03 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/15 17:59:56 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	portal_orientation(t_pge *game, char *portal)
{
	if (game->player->t == 1)
		*portal = 'E';
	else if (game->player->t == -1)
		*portal = 'W';
	else if (game->player->t == -2)
		*portal = 'N';
	else if (game->player->t == 2)
		*portal = 'S';
}

void	check_portal(t_pge *game)
{
	if (game->portal->portal == 1)
	{
		if (game->cub->map[game->player->target.y][game->player->target.x] == '1')
		{
			game->cub->map[game->player->portalb.y][game->player->portalb.x] = '1';
			game->cub->map[game->player->target.y][game->player->target.x] = 'B';
			game->player->portalb = set_vector(game->player->target.x, game->player->target.y);
			portal_orientation(game, &game->player->pb);
			game->portal->clicked_blue = true;
		}
		game->portal->portal = 0;
	}
	else if (game->portal->portal == 2)
	{
		if (game->cub->map[game->player->target.y][game->player->target.x] == '1')
		{
			game->cub->map[game->player->portalo.y][game->player->portalo.x] = '1';
			game->cub->map[game->player->target.y][game->player->target.x] = 'O';
			game->player->portalo = set_vector(game->player->target.x, game->player->target.y);
			portal_orientation(game, &game->player->po);
			game->portal->clicked_orange = true;
		}
		game->portal->portal = 0;
	}
}

int	portal_side_check(t_pge *game, t_raycast *ray, char p)
{
	char	c;

	if (p == 'B')
		c = game->player->pb;
	else
		c = game->player->po;
	if (ray->side == 0)
	{
		if (ray->step.x < 0 && c == 'W')
			return (1);
		else if (c == 'E')
			return (1);
	}
	else if (ray->side == 1)
	{
		if (ray->step.y < 0 && c == 'N')
			return (1);
		else if (c == 'S')
			return (1);
	}
	return (0);
}

int	is_a_portal(t_pge *game, t_raycast *ray)
{
	if (game->cub->map[ray->map.y][ray->map.x] == 'B')
	{
		if (game->portal->clicked_orange == false)
			return (1);
		return (1);
	}
	if (game->cub->map[ray->map.y][ray->map.x] == 'O')
	{
		if (game->portal->clicked_blue == false)
			return (1);
		return (1);
	}
	return (0);
}

t_vf	set_portal_value(t_pge *game, t_raycast *ray, char dir)
{
	char	a;
	char	b;

	if (dir == 'B')
	{
		a = game->player->po;
		b = game->player->pb;
	}
	else
	{
		a = game->player->pb;
		b = game->player->po;
	}
	if (a == b)
		return (same_side(game, ray, dir));
	else if ((a == 'N' && b == 'S') || (a == 'S' && b == 'N')
		|| (a == 'W' && b == 'E') || (a == 'E' && b == 'W'))
		return (opposite_side(game, ray, dir));
	else if ((a == 'N' && b == 'E') || (a == 'E' && b == 'S')
		|| (a == 'S' && b == 'W') || (a == 'W' && b == 'N'))
		return (right_side(game, ray, dir));
	else if ((a == 'N' && b == 'W') || (a == 'W' && b == 'S')
		|| (a == 'S' && b == 'E') || (a == 'E' && b == 'N'))
		return (left_side(game, ray, dir));
	return (set_vectorf(0, 0));
}
