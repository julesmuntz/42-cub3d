/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:30:17 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/05 18:31:12 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cub2(t_cub *cub)
{
	cub->map_depth = 0.0f;
	cub->player_pos.x = 0;
	cub->player_pos.y = 0;
	cub->player_angle = 0.0f;
	cub->map_width = 0;
	cub->map_height = 0;
	cub->valid_map = false;
	cub->searching_for_map = false;
	cub->unreachable_areas = false;
	cub->wall_found = false;
	cub->invalid_map = false;
}

t_cub	*init_cub(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->north_tex_path = NULL;
	cub->south_tex_path = NULL;
	cub->west_tex_path = NULL;
	cub->east_tex_path = NULL;
	cub->floor_color = NULL;
	cub->ceiling_color = NULL;
	cub->map = NULL;
	cub->north_found = false;
	cub->south_found = false;
	cub->west_found = false;
	cub->east_found = false;
	cub->ceiling_found = false;
	cub->floor_found = false;
	cub->map_found = false;
	cub->player_found = false;
	cub->multiple_players = false;
	init_cub2(cub);
	return (cub);
}
