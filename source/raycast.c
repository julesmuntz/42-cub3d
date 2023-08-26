/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:44:42 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/26 18:28:23 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_init(t_pge *game)
{
	t_raycast	ray;

	ray.xy.x = 0;
	while (ray.xy.x < game->drawing_img.width)
	{
		ray.cameraX = (float)ray.xy.x / (float)game->drawing_img.width * 2.f - 1.f;
		ray.rayDir.x = game->player->dir.x + game->player->plan.x * ray.cameraX;
		ray.rayDir.y = game->player->dir.y + game->player->plan.y * ray.cameraX;
		ray.map.x = (int)game->player->pos.x;
		ray.map.y = (int)game->player->pos.y;
		ray.deltaDist.x = fabsf(1.f / ray.rayDir.x);
		ray.deltaDist.y = fabsf(1.f / ray.rayDir.y);
		ray.hit = 0;
		raycast_dda(game, &ray);
		ray.xy.x++;
	}
}

void	raycast_dda(t_pge *game, t_raycast *ray)
{
	if (ray->rayDir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (game->player->pos.x - (float)ray->map.x) *
			ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = ((float)ray->map.x + 1.0f - game->player->pos.x) *
			ray->deltaDist.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (game->player->pos.y - (float)ray->map.y) *
			ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = ((float)ray->map.y + 1.0f - game->player->pos.y) *
			ray->deltaDist.y;
	}
	raycast_dda_collision(game, ray);
}

void	raycast_dda_collision(t_pge *game, t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->map.y += ray->deltaDist.y;
			ray->side = 1;
		}
		if (game->cub->map[ray->map.y][ray->map.x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->wallDist = ray->sideDist.x - ray->deltaDist.x;
	else
		ray->wallDist = ray->sideDist.y - ray->deltaDist.y;
	raycast_dda_setup(game, ray);
}

void	raycast_dda_setup(t_pge *game, t_raycast *ray)
{
	t_xpm	*texture;

	ray->wallSize = (float)game->drawing_img.height / ray->wallDist *
		(game->drawing_img.height / (float)game->drawing_img.width);
	ray->ceiling = (float)game->drawing_img.height / 2.f -
		ray->wallSize / 2.f;
	ray->floor = ray->ceiling + ray->wallSize;
	if (ray->side == 0)
		ray->wallX = game->player->pos.y + ray->rayDir.y;
	else
		ray->wallX = game->player->pos.x + ray->rayDir.x; 
	ray->wallX -= (int)ray->wallX;
	ray->wallX = 1.0f - ray->wallX;
	if ((ray->side == 0 && ray->rayDir.x < 0) || (ray->side == 1 && ray->rayDir.y > 0))
		ray->wallX = 1.0f - ray->wallX;
	texture = texture_choice(ray->side, &ray->step, game);
	raycast_dda_trace(game, ray, texture);
}

void	raycast_dda_trace(t_pge *game, t_raycast *ray, t_xpm *texture)
{
	t_pxl		pxl;

	ray->xy.y = 0;
	while (ray->xy.y < game->drawing_img.height)
	{
		if (ray->xy.y < ray->ceiling)
			pxl = set_pxl_argb(game->cub->ceiling_color[R], game->cub->ceiling_color[G], game->cub->ceiling_color[B], 0);
		else if (ray->xy.y < ray->floor)
			get_pixel_from_xpm(texture, (int)(ray->wallX * texture->width), (int)((float)(ray->xy.y - ray->ceiling) / (float)(ray->floor - ray->ceiling) * texture->height), &pxl);
		else
			pxl = set_pxl_argb(game->cub->floor_color[R], game->cub->floor_color[G], game->cub->floor_color[B], 0);
		draw_pixel(&ray->xy, game, &game->drawing_img, &pxl);
		ray->xy.y++;
	}
}
