/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:49:45 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/24 19:08:10 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_texture(char *line, char str[2], bool *texture_found)
{
	if (line[0] == str[0] && line[1] == str[1] && line[2] == ' '
		&& *texture_found == true)
		return (1);
	if (line[0] == str[0] && line[1] == str[1] && line[2] == ' ')
		*texture_found = true;
	return (0);
}

static int	find_color(char *line, char letter, bool *color_found)
{
	if (line[0] == letter && line[1] == ' ' && ft_isdigit(line[2])
		&& *color_found == true)
		return (1);
	if (line[0] == letter && line[1] == ' ' && ft_isdigit(line[2]))
		*color_found = true;
	return (0);
}

static int	find_map(char *line, int fd, bool *map_found)
{
	(void)line;
	(void)map_found;
	(void)fd;
	//T.B.C.
	return (0);
}

int	check_file(t_pge *game, char *arg)
{
	int		fd;
	char	*line;
	bool	searching_for_map;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	searching_for_map = false;
	while (line)
	{
		if (find_texture(line, "NO", &game->cub->north_found)
			|| find_texture(line, "SO", &game->cub->south_found)
			|| find_texture(line, "WE", &game->cub->west_found)
			|| find_texture(line, "EA", &game->cub->east_found))
			return (print_error("Duplicates texture(s)"), free(line), close(fd),
				1);
		if (find_color(line, 'C', &game->cub->ceiling_found) || find_color(line,
				'F', &game->cub->floor_found))
			return (print_error("Duplicates color(s)"), free(line), close(fd),
				1);
		if (game->cub->north_found && game->cub->south_found
			&& game->cub->west_found && game->cub->east_found
			&& game->cub->ceiling_found && game->cub->floor_found)
		{
			searching_for_map = true;
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (searching_for_map)
		find_map(line, fd, &game->cub->map_found);
	close(fd);
	if (!game->cub->north_found || !game->cub->south_found
		|| !game->cub->west_found || !game->cub->east_found)
		return (print_error("Missing texture(s)"), 1);
	if (!game->cub->ceiling_found || !game->cub->floor_found)
		return (print_error("Missing color(s)"), 1);
	// if (game->cub->map_found == false)
	// 	return (print_error("Missing map"), 1);
	// if (game->cub->multiple_players == true)
	// 	return (print_error("Multiple players"), 1);
	// if (game->cub->player_found == false)
	// 	return (print_error("Player not found"), 1);
	if (init_colors(game, arg))
		return (1);
	if (init_map(game, arg))
		return (1);
	if (init_textures(game, arg))
		return (1);
	return (0);
}
