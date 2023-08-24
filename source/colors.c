/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:25:37 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/24 19:01:57 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*get_color(char letter, char *arg)
{
	int		fd;
	int		*rgb;
	char	*line;
	bool	color_found;
	int		i;
	char	**s_rgb;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (NULL);
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	color_found = false;
	line = get_next_line(fd);
	while (line)
	{
		if (color_found == true)
		{
			free(line);
			break ;
		}
		if (line[0] == letter && line[1] == ' ' && ft_isdigit(line[2]))
		{
			i = -1;
			color_found = true;
			while (line[++i])
			{
				s_rgb = ft_split(line + 2, ',');
				if (!s_rgb[R] || !s_rgb[G] || !s_rgb[B] || s_rgb[3])
					return (print_error("Invalid color format"), free(rgb),
						ft_free_lines(s_rgb), free(line), close(fd), NULL);
				s_rgb[B] = ft_strtrim(s_rgb[B], "\n");
				if (!ft_str_is(ft_isdigit, s_rgb[R]) || !ft_str_is(ft_isdigit,
						s_rgb[G]) || !ft_str_is(ft_isdigit, s_rgb[B]))
					return (print_error("Invalid color value"), free(rgb),
						ft_free_lines(s_rgb), free(line), close(fd), NULL);
				rgb[R] = ft_atoi(s_rgb[R]);
				rgb[G] = ft_atoi(s_rgb[G]);
				rgb[B] = ft_atoi(s_rgb[B]);
				ft_free_lines(s_rgb);
				if (rgb[R] < 0 || rgb[R] > 255 || rgb[G] < 0 || rgb[G] > 255
					|| rgb[B] < 0 || rgb[B] > 255)
					return (print_error("Invalid color range\n0-255 is valid"),
						free(rgb), free(line), close(fd), NULL);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rgb);
}

int	init_colors(t_pge *game, char *arg)
{
	game->cub->ceiling_color = get_color('C', arg);
	if (!game->cub->ceiling_color)
		return (1);
	game->cub->floor_color = get_color('F', arg);
	if (!game->cub->floor_color)
		return (1);
	return (0);
}

int	rgb_to_hex(int *rgb)
{
	return (((rgb[R] & 0xff) << 16) + ((rgb[G] & 0xff) << 8) + (rgb[B] & 0xff));
}
