/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:16:08 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/11 17:05:10 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_texture_path(char str[2], char *arg)
{
	int		fd;
	char	*path;
	char	*line;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == str[0] && line[1] == str[1] && line[2] == ' ')
		{
			path = ft_strndup(line + 3, ft_strlen(line + 3) - 1);
			free(line);
			close(fd);
			return (path);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (NULL);
}

static bool	valid_texture(char *tex_path)
{
	int	fd;

	if (!tex_path)
		return (false);
	fd = open(tex_path, O_RDONLY);
	if (fd == -1)
		return (printf("\033[0;31mError\n\
Failed to load \"%s\"\n\033[0;0m", tex_path), false);
	close(fd);
	return (true);
}

int	init_textures(t_pge *game, char *arg)
{
	bool	failure;

	failure = false;
	game->cub->north_tex_path = get_texture_path("NO", arg);
	if (!valid_texture(game->cub->north_tex_path))
		failure = true;
	game->cub->south_tex_path = get_texture_path("SO", arg);
	if (!valid_texture(game->cub->south_tex_path))
		failure = true;
	game->cub->west_tex_path = get_texture_path("WE", arg);
	if (!valid_texture(game->cub->west_tex_path))
		failure = true;
	game->cub->east_tex_path = get_texture_path("EA", arg);
	if (!valid_texture(game->cub->east_tex_path))
		failure = true;
	if (failure == true)
		return (1);
	return (0);
}
