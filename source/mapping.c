/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:00:51 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/19 12:53:16 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_map_dimensions(char *arg, int *map_width, int *map_height)
{
	int		fd;
	char	*line;
	int		row_length;
	int		space_count;

	*map_width = 0;
	*map_height = 0;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return perror("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		space_count = 0;
		while (ft_isspace(line[space_count]))
			space_count++;
		if (line[space_count] == '1')
		{
			row_length = space_count;
			while (line[row_length] != '\0')
				row_length++;
			if (row_length > *map_width)
				*map_width = row_length;
			(*map_height)++;
		}
		free(line);
	}
	close(fd);
}

static char	**get_map(int fd)
{
	char	*line;
	bool	map_found;
	int		row_index;
	int		col_index;
	int		space_count;

	row_index = 0;
	map_found = false;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!map_found && line[0] == ' ')
		{
			space_count = 0;
			while (line[space_count] == ' ')
				space_count++;
			if (line[space_count] == '1')
				map_found = true;
		}
		else if (line[0] == '1')
			map_found = true;
		if (map_found)
		{
			col_index = 0;
			while (line[col_index] != '\0')
			{
				if (line[col_index] == 'N' || line[col_index] == 'S'
					|| line[col_index] == 'E' || line[col_index] == 'W')
				{
					g_player_x = (float)col_index;
					g_player_y = (float)row_index;
					break ;
				}
				col_index++;
			}
			g_map[row_index] = line;
			row_index++;
		}
		else
			free(line);
	}
	g_map[row_index] = NULL;
	close(fd);
	return (g_map);
}

int	init_map(char *arg)
{
	int	map_width;
	int	map_height;
	int	fd;

	calculate_map_dimensions(arg, &map_width, &map_height);
	if (map_width > map_height)
		g_map_depth = map_width;
	else
		g_map_depth = map_height;
	g_map = (char **)malloc(sizeof(char *) * (map_height + 1));
	if (!g_map)
		return (perror("Failed to allocate memory for g_map"), 1);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to reopen file");
		free(g_map);
		return (1);
	}
	g_map = get_map(fd);
	return (0);
}
