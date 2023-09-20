/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:44:42 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/20 16:17:35 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_init(t_pge *game, t_vf start, t_xpm *img)
{
	t_raycast	*ray;

	ray = game->ray;
	ray->xy.x = 0;
	while (ray->xy.x < game->drawing_img.width)
	{
		ray->walldist = 0;
		ray->start = start;
		ray->camerax = (float)ray->xy.x / (float)game->drawing_img.width * 2.f
			- 1.f;
		ray->raydir.x = game->player->dir.x + game->player->plan.x
			* ray->camerax;
		ray->raydir.y = game->player->dir.y + game->player->plan.y
			* ray->camerax;
		ray->map.x = start.x;
		ray->map.y = start.y;
		ray->deltadist.x = fabsf(1.f / ray->raydir.x);
		ray->deltadist.y = fabsf(1.f / ray->raydir.y);
		ray->hit = 0;
		raycast_dda(game, ray, &start, img);
		ray->xy.x++;
	}
}

void	raycast_dda(t_pge *game, t_raycast *ray, t_vf *start, t_xpm *img)
{
	if (ray->raydir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (start->x - (float)ray->map.x)
			* ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = ((float)ray->map.x + 1.0f - start->x)
			* ray->deltadist.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (start->y - (float)ray->map.y)
			* ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = ((float)ray->map.y + 1.0f - start->y)
			* ray->deltadist.y;
	}
	raycast_dda_collision(game, ray, img);
}

void	raycast_dda_collision(t_pge *game, t_raycast *ray, t_xpm *img)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (check_collision_ray(game, ray) == 1)
			ray->hit = 1;
		if (check_collision_ray(game, ray) == -1)
			return ;
	}
	if (ray->side == 0)
		ray->walldist = (ray->sidedist.x - ray->deltadist.x);
	else
		ray->walldist = (ray->sidedist.y - ray->deltadist.y);
	raycast_dda_setup(game, ray, img);
}

void	raycast_dda_setup(t_pge *game, t_raycast *ray, t_xpm *img)
{
	t_xpm	*texture;

	ray->wallsize = (float)game->drawing_img.height / ray->walldist;
	ray->ceiling = (float)(game->drawing_img.height) / 2.f - ray->wallsize / 2.f
		+ game->player->pitch * 25;
	ray->floor = ray->ceiling + ray->wallsize;
	if (ray->side == 0)
		ray->wallx = game->player->pos.y + ray->walldist * ray->raydir.y;
	else
		ray->wallx = game->player->pos.x + ray->walldist * ray->raydir.x;
	ray->wallx -= (int)(ray->wallx);
	ray->wallx = 1.0f - ray->wallx;
	if ((ray->side == 0 && ray->raydir.x < 0) || (ray->side == 1
			&& ray->raydir.y > 0))
		ray->wallx = 1.0f - ray->wallx;
	texture = texture_choice(ray, game);
	if (ray->xy.x == game->drawing_img.width / 2)
	{
		game->player->target = copy_vector(&ray->map);
		if (ray->side == 0)
			game->player->t = 1 * ray->step.x;
		else
			game->player->t = 2 * ray->step.y;
	}
	raycast_dda_trace(game, ray, texture, img);
}

void	raycast_dda_trace(t_pge *game, t_raycast *ray, t_xpm *texture, t_xpm *img)
{
	t_pxl	pxl;
	float	dist;

	ray->xy.y = 0;
	dist = 0;
	while (ray->xy.y < game->drawing_img.height)
	{
		if (ray->walldist >= game->cub->map_depth)
			pxl = set_pxl_argb(0, 0, 0, 0);
		else
		{
			set_pxl_for_dda(game, texture, &dist, &pxl);
			fog_generation(&pxl, &dist, game);
		}
		draw_pixel(&ray->xy, img, &pxl);
		ray->xy.y++;
	}
}
