/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:49:45 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/11 14:38:05 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture(char *line, char str[2], bool *texture_found)
{
	if (line[0] == str[0] && line[1] == str[1] && line[2] == ' '
		&& *texture_found == true)
		return (1);
	if (line[0] == str[0] && line[1] == str[1] && line[2] == ' ')
		*texture_found = true;
	return (0);
}

static int	check_color(char *line, char letter, bool *color_found)
{
	if (line[0] == letter && line[1] == ' ' && ft_isdigit(line[2])
		&& *color_found == true)
		return (1);
	if (line[0] == letter && line[1] == ' ' && ft_isdigit(line[2]))
		*color_found = true;
	return (0);
}

static int	check_texture_and_color(t_pge *game, char *line)
{
	if (check_texture(line, "NO", &game->cub->north_found)
		|| check_texture(line, "SO", &game->cub->south_found)
		|| check_texture(line, "WE", &game->cub->west_found)
		|| check_texture(line, "EA", &game->cub->east_found))
	{
		print_error("Duplicates texture(s)");
		free(line);
		return (1);
	}
	if (check_color(line, 'C', &game->cub->ceiling_found)
		|| check_color(line, 'F', &game->cub->floor_found))
	{
		print_error("Duplicates color(s)");
		free(line);
		return (1);
	}
	return (0);
}

static int	end(t_pge *game, char *arg)
{
	check_map(game, arg);
	if (!game->cub->north_found || !game->cub->south_found
		|| !game->cub->west_found || !game->cub->east_found)
		return (print_error("Missing texture(s)"), 1);
	if (init_textures(game, arg))
		return (1);
	if (!game->cub->ceiling_found || !game->cub->floor_found)
		return (print_error("Missing color(s)"), 1);
	if (init_colors(game, arg))
		return (1);
	if (game->cub->door_found == true)
		return (print_error("Door(s) found"), 1);
	if (game->cub->multiple_players == true)
		return (print_error("Multiple players"), 1);
	if (game->cub->valid_map == false || game->cub->invalid_map == true)
		return (print_error("Invalid map"), 1);
	if (game->cub->map_found == false || game->cub->wall_found == false)
		return (print_error("Missing map"), 1);
	if (game->cub->player_found == false)
		return (print_error("Player not found"), 1);
	if (game->cub->unreachable_areas == true)
		return (print_error("Unreachable area(s)"), 1);
	if (init_map(game, arg))
		return (1);
	return (0);
}

int	check_file(t_pge *game, char *arg)
{
	int		fd;
	char	*line;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (print_error("File not found"), 1);
	if (invalid_extension(arg))
		return (print_error("Invalid file extension (.cub)"), close(fd), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (check_texture_and_color(game, line))
			return (close(fd), 1);
		if (game->cub->north_found && game->cub->south_found
			&& game->cub->west_found && game->cub->east_found
			&& game->cub->ceiling_found && game->cub->floor_found)
		{
			game->cub->searching_for_map = true;
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), end(game, arg));
}
