/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:51:36 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/22 13:03:55 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_por
{
	t_vi	port;
	char	dir;
}	t_por;

static char const	g_dirs[4] = "NESW";

static inline t_vf	__set_ray(
		t_por const *const port1,
		t_por const *const port2,
		t_raycast const *const ray,
		t_raycast *const new_ray)
{
	int const	rside1 = ft_strchr(g_dirs, port1->dir) - g_dirs;
	int const	rside2 = ft_strchr(g_dirs, port2->dir) - g_dirs;
	t_vi const	diff = {port2->port.x - port1->port.x, port2->port.y - port1->port.y};
	t_vf		off;
	t_vf		start;

	start = (t_vf){ray->map.x + diff.x, ray->map.y + diff.y};
	off = (t_vf){ray->end.x - (((float)port1->port.x) + 0.5f), ray->end.y - (((float)port1->port.y) + 0.5f)};
	printf("---======---\n");
	printf("before tp'd ray pos : %f %f\n", ray->end.x, ray->end.y);
	printf("ray off : %f %f\n", off.x, off.y);
	if (port1->dir == port2->dir)
	{
		printf("Same side\n");
		if (ray->side == 0)
		{
			new_ray->raydir.x = -ray->raydir.x;
			off.x = -off.x;
		}
		else
		{
			new_ray->raydir.y = -ray->raydir.y;
			off.y = -off.y;
		}
	}
	else if (((rside1 + 1) & 3) == rside2)
	{
		printf("Rotate to right\n");
		new_ray->raydir.x = ray->raydir.y;
		new_ray->raydir.y = -ray->raydir.x;
		off.x = off.y;
		off.y = -off.x;
	}
	else if (((rside1 - 1) & 3) == rside2)
	{
		printf("Rotate to left\n");
		new_ray->raydir.x = -ray->raydir.y;
		new_ray->raydir.y = ray->raydir.x;
		off.x = -off.y;
		off.y = off.x;
	}
	else
	{
		printf("Going straight\n");
		new_ray->raydir = ray->raydir;
		if (ray->side == 0)
			off.x = -off.x;
		else
			off.y = -off.y;
	}
	start = (t_vf){start.x + 0.5f + off.x, start.y + 0.5f + off.y};
	printf("tp'd ray pos : %f %f\n", start.x, start.y);
	printf("---======---\n");
	return (start);
}

void	raycast_portal(t_pge *game, t_raycast *ray, float walldist, char dir)
{
	t_vf		start;
	t_raycast	rcast;
	t_por		portal1;
	t_por		portal2;

	(void)dir;
	(void)walldist;
	rcast = *ray;
	if (rcast.map.x == game->player->portalo.x && rcast.map.y == game->player->portalo.y)
	{
		portal1 = (t_por){game->player->portalo, game->player->po};
		portal2 = (t_por){game->player->portalb, game->player->pb};
	}
	else
	{
		portal1 = (t_por){game->player->portalb, game->player->pb};
		portal2 = (t_por){game->player->portalo, game->player->po};
	}
	// rcast.walldist += walldist;
	start = __set_ray(&portal1, &portal2, ray, &rcast);
	rcast.start = start;
	ray->map.x = start.x;
	ray->map.y = start.y;
	rcast.deltadist.x = fabsf(1.f / rcast.raydir.x);
	rcast.deltadist.y = fabsf(1.f / rcast.raydir.y);
	rcast.hit = 0;
	rcast.crossed++;
	raycast_dda(game, &rcast, &start, &game->drawing_img);
}

char	get_side(t_raycast	*ray)
{
	if (ray->side == 0)
	{
		if (ray->step.x < 0)
			return ('W');
		else
			return ('E');
	}
	else if (ray->side == 1)
	{
		if (ray->step.y < 0)
			return ('N');
		else
			return ('S');
	}
	return (0);
}

int	check_side(t_pge *game, t_raycast *ray, char p)
{
	if (p == 'B')
	{
		if (game->player->pb == get_side(ray))
		{
			printf("est sur le meme side\n");
			return (1);
		}
		return (0);
	}
	if (p == 'O')
	{
		if (game->player->po == get_side(ray))
		{
			printf("est sur le meme side\n");
			return (1);
		}
		return (0);
	}
	return (0);
}
