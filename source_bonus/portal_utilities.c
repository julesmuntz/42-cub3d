/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:23:02 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/15 18:45:26 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vf	same_side(t_pge *game, t_raycast *ray, char dir)
{
	t_vf	start;
	t_vf	delta_block;
	t_vi	portal_diff;
	t_vi	portal1;
	t_vi	portal2;

	ray->end = set_vectorf(
			ray->start.x + ray->walldist * ray->raydir.x,
			ray->start.y + ray->walldist * ray->raydir.y);
	// printf("end [%f, %f]\nstart [%f, %f], dist[%f]\n", ray->end.x, ray->end.y, ray->start.x, ray->start.y, ray->walldist);
	printf("===============\nstart [%f, %f]\n", ray->end.x, ray->end.y);
	portal1 = game->player->portalo;
	portal2 = game->player->portalb;
	if (dir == 'B')
	{
		portal1 = game->player->portalb;
		portal2 = game->player->portalo;
	}
	delta_block.x = ray->end.x - (portal1.x + 0.5f);
	delta_block.y = ray->end.y - (portal1.y + 0.5f);
	portal_diff = set_vector(portal2.x - portal1.x, portal2.y - portal1.y);
	// delta_block = set_vectorf(-delta_block.x, delta_block.y);
	start = set_vectorf(
		ray->end.x + portal_diff.x + delta_block.x - 0.5f,
		ray->end.y + portal_diff.y + delta_block.y - 0.5f);
	printf("new end [%f, %f]\n", start.x, start.y);
	printf("ray dir [%f, %f]\n", ray->raydir.x, ray->raydir.y);
	if (ray->side == 0)
		ray->raydir = set_vectorf(-ray->raydir.x, ray->raydir.y);
	else
		ray->raydir = set_vectorf(ray->raydir.x, -ray->raydir.y);
	printf("new ray dir [%f, %f]\n", ray->raydir.x, ray->raydir.y);
	// printf("start [%f, %f]\n", start.x, start.y);
	// printf("end [%f, %f]\n", ray->end.x, ray->end.y);
	return (start);
}
	// t_vi	dif;

	// ray->raydir = set_vectorf(ray->raydir.x * -1, ray->raydir.y * -1);
	// dif = set_vector((game->player->portalb.x - game->player->portalo.x),
	// 	(game->player->portalb.y - game->player->portalo.y));
	// if ((dir == 'B' && game->player->portalb.x > game->player->portalo.x)
	// 	|| (dir == 'O' && game->player->portalo.x > game->player->portalb.x))
	// 	start.x = ray->sidedist.x + dif.x;
	// else
	// 	start.x = ray->sidedist.x + dif.x + 1;
	// if ((dir == 'B' && game->player->portalb.y > game->player->portalo.y)
	// 	|| (dir == 'O' && game->player->portalo.y > game->player->portalb.y))
	// 	start.y = ray->sidedist.y + dif.y;
	// else
	// 	start.y = ray->sidedist.y + dif.y + 1;

t_vf	opposite_side(t_pge *game, t_raycast *ray, char dir)
{
	t_vf	start;
	t_vi	dif;

	dif = set_vector((game->player->portalb.x - game->player->portalo.x),
		(game->player->portalb.y - game->player->portalo.y));
	if ((dir == 'B' && game->player->portalb.x > game->player->portalo.x)
		|| (dir == 'O' && game->player->portalo.x > game->player->portalb.x))
		start.x = ray->sidedist.x + dif.x;
	else
		start.x = ray->sidedist.x + dif.x + 1;
	if ((dir == 'B' && game->player->portalb.y > game->player->portalo.y)
		|| (dir == 'O' && game->player->portalo.y > game->player->portalb.y))
		start.y = ray->sidedist.y + dif.y;
	else
		start.y = ray->sidedist.y + dif.y + 1;
	return (start);
}

t_vf	right_side(t_pge *game, t_raycast *ray, char dir)
{
	t_vf	start;
	t_vi	dif;

	ray->raydir = set_vectorf(ray->raydir.y * -1, ray->raydir.x * -1);
	dif = set_vector((game->player->portalb.x - game->player->portalo.x),
		(game->player->portalb.y - game->player->portalo.y));
	if ((dir == 'B' && game->player->portalb.x > game->player->portalo.x)
		|| (dir == 'O' && game->player->portalo.x > game->player->portalb.x))
		start.x = ray->sidedist.x + dif.x;
	else
		start.x = ray->sidedist.x + dif.x + 1;
	if ((dir == 'B' && game->player->portalb.y > game->player->portalo.y)
		|| (dir == 'O' && game->player->portalo.y > game->player->portalb.y))
		start.y = ray->sidedist.y + dif.y;
	else
		start.y = ray->sidedist.y + dif.y + 1;
	return (start);
}

t_vf	left_side(t_pge *game, t_raycast *ray, char dir)
{
	t_vf	start;
	t_vi	dif;

	ray->raydir = set_vectorf(ray->raydir.y * -1, ray->raydir.x);
	dif = set_vector((game->player->portalb.x - game->player->portalo.x),
		(game->player->portalb.y - game->player->portalo.y));
	if ((dir == 'B' && game->player->portalb.x > game->player->portalo.x)
		|| (dir == 'O' && game->player->portalo.x > game->player->portalb.x))
		start.x = ray->sidedist.x + dif.x;
	else
		start.x = ray->sidedist.x + dif.x + 1;
	if ((dir == 'B' && game->player->portalb.y > game->player->portalo.y)
		|| (dir == 'O' && game->player->portalo.y > game->player->portalb.y))
		start.y = ray->sidedist.y + dif.y;
	else
		start.y = ray->sidedist.y + dif.y + 1;
	return (start);
}

int	check_collision_ray(t_pge *game, t_raycast *ray)
{
	float	walldist;

	if (ray->side == 0)
		walldist = ray->walldist + (ray->sidedist.x - ray->deltadist.x);
	else
		walldist = ray->walldist + (ray->sidedist.y - ray->deltadist.y);
	if (ray->map.x < 0 || ray->map.y < 0 || ray->map.x >= game->cub->map_width
		|| ray->map.y >= game->cub->map_height)
	{
		printf("en dehors de la map\n");
		return (1);
	}
	if (walldist >= game->cub->map_depth)
		return (1);
	if (game->cub->map[ray->map.y][ray->map.x] == '1')
		return (1);
	if (is_a_portal(game, ray) == 1)
		return (1);
	if (game->cub->map[ray->map.y][ray->map.x] == 'D'
		&& door_is_close(game, ray->map.x, ray->map.y) == 1)
		return (1);
	return (0);
}
