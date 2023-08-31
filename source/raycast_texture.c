/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:10:06 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/31 15:33:40 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_xpm	*texture_choice(int const side, t_vi const *step, t_pge const *game)
{
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
			/ (vector_dist(&maxdist) - 0.1f)) + game->ray->wallDist
		* ((vector_dist(&dist) - 0.1f) / (vector_dist(&maxdist) - 0.1f)));
	if (d < 1.f)
		d = 0.f;
	return (d);
}
