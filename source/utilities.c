/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:09:13 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/28 16:21:35 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

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

void	print_error(char *str)
{
	write(STDERR_FILENO, "\033[0;31mError\n", 13);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n\033[0;0m", 7);
}

bool	invalid_extension(char *filename)
{
	char	*cub;

	if (!filename)
		return (true);
	cub = ft_strrchr(filename, '.');
	if (!cub || ft_strncmp(cub, ".cub\0", 5))
		return (true);
	return (false);
}
