/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:10:06 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/05 16:38:47 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_xpm	*texture_choice(int const side, t_vi const *step, t_pge const *game)
{
	if (game->cub->map[game->ray->map.y][game->ray->map.x] == 'D')
		return (find_xpm(game->xpm, "door"));
	if (side == 0)
	{
		if (step->x < 0)
			return (find_xpm(game->xpm, "west"));
		else
			return (find_xpm(game->xpm, "east"));
	}
	else
	{
		if (step->y < 0)
			return (find_xpm(game->xpm, "north"));
		else
			return (find_xpm(game->xpm, "south"));
	}
}

int	add_texture(t_pge *game)
{
	game->xpm = game_add_xpm(game->cub->east_tex_path, "east", game->xpm, game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm(game->cub->north_tex_path, "north", game->xpm,
			game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm(game->cub->south_tex_path, "south", game->xpm,
			game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm(game->cub->west_tex_path, "west", game->xpm, game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm(game->portal->portalgun_ent_path, "gun", game->xpm,
			game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm(game->portal->crosshair_ent_path, "crosshair",
			game->xpm, game);
	if (!game->xpm)
		return (0);
	if (add_portal_texture(game) == 0)
		return (0);
	return (1);
}

void	fog_generation(t_pxl *pxl, float *dist, t_pge *game)
{
	t_pxl	fog;

	set_pxl_hex(0, &fog);
	if (*dist < 0.01f)
		return ;
	if (*dist > game->cub->map_depth)
		*pxl = fog;
	else
		*pxl = pixel_interpolation(pxl, &fog, *dist,
				game->cub->map_depth);
}

float	dist_interpolation(t_pge *game)
{
	t_vi	center;
	t_vi	floor;
	t_vi	dist;
	t_vi	maxdist;
	float	d;

	center = set_vector(game->drawing_img.width / 2, game->drawing_img.height);
	floor = set_vector(game->ray->xy.x, game->ray->floor + 1);
	dist = set_vector_by_points(&game->ray->xy, &center);
	maxdist = set_vector_by_points(&floor, &center);
	d = (0.1 * ((vector_dist(&maxdist) - vector_dist(&dist))
				/ (vector_dist(&maxdist) - 0.1f)) + game->ray->walldist
			* ((vector_dist(&dist) - 0.1f) / (vector_dist(&maxdist) - 0.1f)));
	if (d < 1.f)
		d = 0.f;
	return (d);
}

void	set_pxl_for_dda(t_pge *game, t_xpm *texture, float *dist, t_pxl *pxl)
{
	t_raycast	*ray;

	ray = game->ray;
	if (ray->xy.y < ray->ceiling)
	{
		*pxl = set_pxl_argb(game->cub->ceiling_color[R],
				game->cub->ceiling_color[G],
				game->cub->ceiling_color[B], 0);
		*dist = ray->walldist;
	}
	else if (ray->xy.y < ray->floor)
	{
		get_pixel_from_xpm(texture, (int)(ray->wallx * texture->width),
			(int)((float)(ray->xy.y - ray->ceiling) / (float)(ray->floor
					- ray->ceiling) * texture->height), pxl);
		*dist = ray->walldist;
	}
	else
	{
		*pxl = set_pxl_argb(game->cub->floor_color[R],
				game->cub->floor_color[G], game->cub->floor_color[B], 0);
		*dist = (float)(game->drawing_img.height - ray->xy.y)
			/ (float)game->drawing_img.height
			* (float)(game->cub->map_depth / 2);
	}
}
