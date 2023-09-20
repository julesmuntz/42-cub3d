/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:23:02 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/20 18:03:37 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_portal_value(t_raycast *ray, t_vf *start, char side)
{
	if (side == 'N')
		*start = set_vectorf(start->x + ray->wallx, start->y);
	else if (side == 'S')
		*start = set_vectorf(start->x + ray->wallx, start->y + 1);
	else if (side == 'W')
		*start = set_vectorf(start->x, start->y + ray->wallx);
	else if (side == 'E')
		*start = set_vectorf(start->x + 1, start->y + ray->wallx);
}

static int	check_portal_sides(char *ref, char out)
{
	int	i;

	i = 0;
	while(ref[i])
	{
		if (ref[i] == out)
			return (i);
		i++;
	}
	return (-1);
}

void	update_portal_ray(t_raycast *ray, char in, char out)
{
	char const n[4] = "ESWN";
	char const e[4] = "SWNE";
	char const s[4] = "WNES";
	char const w[4] = "NESW";
	int			i;

	if (in == 'N')
		i = check_portal_sides((char *)n, out);
	if (in == 'E')
		i = check_portal_sides((char *)e, out);
	if (in == 'S')
		i = check_portal_sides((char *)s, out);
	if (in == 'W')
		i = check_portal_sides((char *)w, out);
	if (i == 0)
		ray->raydir = set_vectorf(ray->raydir.y, -ray->raydir.x);
	else if (i == 2)
		ray->raydir = set_vectorf(-ray->raydir.y, ray->raydir.x);
	else if (i == 3)
		ray->raydir = set_vectorf(-ray->raydir.x, -ray->raydir.y);
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
		printf("player[%f;%f]\n", game->player->pos.x, game->player->pos.y);
		printf("portal blue[%d;%d]\n", game->player->portalb.x, game->player->portalb.y);
		return (-1);
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
