/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:48:03 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/20 16:01:49 by gfranque         ###   ########.fr       */
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
		for (int i = 0; game->cub->map[i]; i++)
			printf("[%s]\n", game->cub->map[i]);
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
		for (int i = 0; game->cub->map[i]; i++)
			printf("[%s]\n", game->cub->map[i]);
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
	t_vf	start;
	char	p;
	char	side;

	p = 0;
	side = 0;
	if (dir == 'B')
	{
		start = set_vectorf(game->player->portalo.x, game->player->portalo.y);
		side = game->player->po;
		p = game->player->pb;
	}
	else if (dir == 'O')
	{
		start = set_vectorf(game->player->portalb.x, game->player->portalb.y);
		side = game->player->pb;
		p = game->player->po;
	}
	(void)dir;
	update_portal_value(ray, &start, side);
	update_portal_ray(ray, p, side);
	return (start);
}
