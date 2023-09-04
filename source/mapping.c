/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:00:51 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/04 16:09:26 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	skip_top_lines(int *count, char **line, int fd)
{
	while (*count != 6)
	{
		if ((*line[0] == 'N' && (*line)[1] == 'O') || (*line[0] == 'S'
				&& (*line)[1] == 'O') || (*line[0] == 'W' && (*line)[1] == 'E')
			|| (*line[0] == 'E' && (*line)[1] == 'A') || (*line[0] == 'F')
			|| (*line[0] == 'C'))
			(*count)++;
		free(*line);
		*line = get_next_line(fd);
	}
}

static void	check_map_start(t_pge *game, char *line, int *sp)
{
	if (!game->cub->map_found && line[0] == ' ')
	{
		*sp = 0;
		while (line[*sp] == ' ')
			(*sp)++;
		if (ft_ismap_char(line[*sp]))
			game->cub->map_found = true;
	}
	else if (!game->cub->map_found && ft_ismap_char(line[0]))
		game->cub->map_found = true;
}

static void	get_map2(t_pge *game, char *line, int row_index)
{
	int	col_index;

	col_index = 0;
	while (line[col_index] != '\0')
	{
		if (line[col_index] == 'N' || line[col_index] == 'S'
			|| line[col_index] == 'E' || line[col_index] == 'W')
		{
			game->cub->player_pos.x = col_index;
			game->cub->player_pos.y = row_index;
			if (line[col_index] == 'N')
				game->cub->player_angle = -M_PI_2;
			else if (line[col_index] == 'S')
				game->cub->player_angle = M_PI_2;
			else if (line[col_index] == 'E')
				game->cub->player_angle = 0.0f;
			else if (line[col_index] == 'W')
				game->cub->player_angle = M_PI;
			break ;
		}
		col_index++;
	}
	game->cub->map[row_index] = ft_strndup(line, ft_strlen(line) - 1);
}

static char	**get_map(t_pge *game, int fd)
{
	char	*line;
	int		row_index;
	int		sp;
	int		count;

	row_index = 0;
	count = 0;
	line = get_next_line(fd);
	if (game->cub->searching_for_map)
		skip_top_lines(&count, &line, fd);
	while (line)
	{
		check_map_start(game, line, &sp);
		if (game->cub->map_found)
		{
			get_map2(game, line, row_index);
			row_index++;
			if (row_index == game->cub->map_height)
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->cub->map[row_index] = NULL;
	return (free(line), close(fd), game->cub->map);
}

int	init_map(t_pge *game, char *arg)
{
	int	fd;

	if (game->cub->map)
		ft_free_lines(game->cub->map);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (1);
	calculate_map_dimensions(game, fd);
	close(fd);
	if (game->cub->map_width > game->cub->map_height)
		game->cub->map_depth = game->cub->map_width;
	else
		game->cub->map_depth = game->cub->map_height;
	game->cub->map = malloc(sizeof(char *) * (game->cub->map_height + 1));
	if (!game->cub->map)
		return (1);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (free(game->cub->map), 1);
	game->cub->map = get_map(game, fd);
	return (0);
}
