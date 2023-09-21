/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:10:06 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/21 14:56:05 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_xpm	*texture_choice(t_raycast *ray, t_pge const *game)
{
	char	c;

	c = get_side(ray);
	if (c == 'W')
		return (find_xpm(game->xpm, "west"));
	else if (c == 'E')
		return (find_xpm(game->xpm, "east"));
	else if (c == 'N')
		return (find_xpm(game->xpm, "north"));
	else if (c == 'S')
		return (find_xpm(game->xpm, "south"));
	return (NULL);
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
				/ (vector_dist(&maxdist) - 0.1f)) + game->ray->walldist
			* ((vector_dist(&dist) - 0.1f) / (vector_dist(&maxdist) - 0.1f)));
	if (d < 1.f)
		d = 0.f;
	return (d);
}
