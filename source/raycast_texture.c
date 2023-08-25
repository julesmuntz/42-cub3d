/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:10:06 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/24 21:08:52 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

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
	game->xpm = game_add_xpm(game->cub->north_tex_path, "north", game->xpm, game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm(game->cub->south_tex_path, "south", game->xpm, game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm(game->cub->west_tex_path, "west", game->xpm, game);
	if (!game->xpm)
		return (0);
	return (1);
}
