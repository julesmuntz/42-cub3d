/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:49:45 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/21 17:09:34 by julmuntz         ###   ########.fr       */
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

int	check_file(t_cub *cub, char *arg)
{
	int		fd;
	char	*line;

	cub->north_found = false;
	cub->south_found = false;
	cub->west_found = false;
	cub->east_found = false;
	cub->ceiling_found = false;
	cub->floor_found = false;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		if (find_texture(line, "NO", &cub->north_found) || find_texture(line,
				"SO", &cub->south_found) || find_texture(line, "WE",
				&cub->west_found) || find_texture(line, "EA", &cub->east_found))
		return (printf("%sError\nDuplicates texture(s)\n%s", RED, NONE),
			free(line), close(fd), 1);
		if (find_color(line, 'C', &cub->ceiling_found)
			|| find_color(line, 'F', &cub->floor_found))
		return (printf("%sError\nDuplicates color(s)\n%s", RED, NONE),
			free(line), close(fd), 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!cub->north_found || !cub->south_found || !cub->west_found
		|| !cub->east_found)
		return (printf("%sError\nMissing texture(s)\n%s", RED, NONE), 1);
	if (!cub->ceiling_found || !cub->floor_found)
		return (printf("%sError\nMissing color(s)\n%s", RED, NONE), 1);
	return (0);
}
