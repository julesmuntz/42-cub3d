/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:49:45 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/25 19:42:48 by julmuntz         ###   ########.fr       */
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

static int	find_map(t_pge *game, char *arg)
{
	int		b;
	int		a;
	int		pos;
	bool	failure;

	b = 0;
	a = 0;
	pos = 0;
	failure = false;
	init_map(game, arg);
	while (game->cub->map[a])
	{
		if (!game->cub->map_found && game->cub->map[a][0] == ' ')
		{
			while (game->cub->map[a][b] == ' ')
				b++;
			if (game->cub->map[a][b] == '1')
				game->cub->map_found = true;
		}
		else if (!game->cub->map_found && game->cub->map[a][0] == '1')
			game->cub->map_found = true;
		if (game->cub->map_found)
		{
			b = 0;
			pos++;
			while (game->cub->map[a][b])
			{
				if (ft_ismap_char(game->cub->map[a][b]) == false)
					failure = true;
				if (ft_ismap_player(game->cub->map[a][b]) == true)
				{
					if (game->cub->player_found == true)
						game->cub->multiple_players = true;
					game->cub->player_found = true;
				}
				if (pos == 1 && (game->cub->map[a][b] == '0'
						|| ft_ismap_player(game->cub->map[a][b])))
					failure = true;
				//W.I.P.
				b++;
			}
		}
		a++;
	}
	if (failure == false)
		game->cub->valid_map = true;
	ft_free_lines(game->cub->map);
	return (0);
}

int	check_file(t_pge *game, char *arg)
{
	int		fd;
	char	*line;
	bool	searching_for_map;

	if (invalid_extension(arg))
		return (print_error("Invalid file extension"), 1);
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
	close(fd);
	if (searching_for_map == true)
		find_map(game, arg);
	if (!game->cub->north_found || !game->cub->south_found
		|| !game->cub->west_found || !game->cub->east_found)
		return (print_error("Missing texture(s)"), 1);
	if (!game->cub->ceiling_found || !game->cub->floor_found)
		return (print_error("Missing color(s)"), 1);
	if (game->cub->map_found == false)
		return (print_error("Missing map"), 1);
	if (game->cub->valid_map == false)
		return (print_error("Invalid map"), 1);
	if (game->cub->multiple_players == true)
		return (print_error("Multiple players"), 1);
	if (game->cub->player_found == false)
		return (print_error("Player not found"), 1);
	if (init_colors(game, arg))
		return (1);
	if (init_map(game, arg))
		return (1);
	if (init_textures(game, arg))
		return (1);
	return (0);
}
