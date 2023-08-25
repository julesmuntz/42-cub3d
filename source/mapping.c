/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:00:51 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/25 19:25:24 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_map_dimensions(t_pge *game, char *arg)
{
	int		fd;
	char	*line;
	int		row_length;
	int		space_count;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		space_count = 0;
		while (ft_isspace(line[space_count]))
			space_count++;
		if (line[space_count] == '1')
		{
			row_length = space_count;
			while (line[row_length] != '\0')
				row_length++;
			if (row_length > game->cub->map_width)
				game->cub->map_width = row_length;
			(game->cub->map_height)++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static char	**get_map(t_pge *game, int fd)
{
	char	*line;
	bool	map_found;
	int		row_index;
	int		col_index;
	int		space_count;

	row_index = 0;
	map_found = false;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_found && line[0] == ' ')
		{
			space_count = 0;
			while (line[space_count] == ' ')
				space_count++;
			if (line[space_count] == '1')
				map_found = true;
		}
		else if (!map_found && line[0] == '1')
			map_found = true;
		if (map_found)
		{
			col_index = 0;
			while (line[col_index] != '\0')
			{
				if (line[col_index] == 'N' || line[col_index] == 'S'
					|| line[col_index] == 'E' || line[col_index] == 'W')
				{
					game->cub->player_pos.x = col_index;
					game->cub->player_pos.y = row_index;
					if (line[col_index] == 'N')
						game->cub->player_angle = 0.0f;
					else if (line[col_index] == 'S')
						game->cub->player_angle = 0.0f;
					else if (line[col_index] == 'E')
						game->cub->player_angle = 0.0f;
					else if (line[col_index] == 'W')
						game->cub->player_angle = 0.0f;
					break;
				}
				col_index++;
			}
			game->cub->map[row_index] = ft_strndup(line, ft_strlen(line)-1);
			row_index++;
			if (row_index == game->cub->map_height)
				break;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	game->cub->map[row_index] = NULL;
	close(fd);
	return (game->cub->map);
}

int	init_map(t_pge *game, char *arg)
{
	int	fd;

	calculate_map_dimensions(game, arg);
	if (game->cub->map_width > game->cub->map_height)
		game->cub->map_depth = game->cub->map_width;
	else
		game->cub->map_depth = game->cub->map_height;
	game->cub->map = (char **)malloc(sizeof(char *) * (game->cub->map_height + 1));
	if (!game->cub->map)
		return (1);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (free(game->cub->map), 1);
	game->cub->map = get_map(game, fd);
	return (0);
}
