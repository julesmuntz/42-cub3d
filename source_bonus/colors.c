/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:25:37 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/13 16:40:30 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	strarr_to_intarr(char **s, int *rgb)
{
	rgb[R] = ft_atoi(s[R]);
	free(s[R]);
	rgb[G] = ft_atoi(s[G]);
	free(s[G]);
	rgb[B] = ft_atoi(s[B]);
	free(s[B]);
	free(s);
}

static char	**rgb_split(char *line)
{
	int		i;
	int		comma[2];
	char	**s;

	i = 0;
	comma[0] = -1;
	comma[1] = -1;
	while (line[i])
	{
		if (line[i] == ',' && comma[0] == -1 && comma[1] == -1)
			comma[0] = i;
		else if (line[i] == ',' && comma[1] == -1 && comma[0] != -1)
			comma[1] = i;
		i++;
	}
	s = (char **)malloc(sizeof(char *) * 4);
	s[R] = ft_strndup(line + 2, comma[0] - 2);
	s[G] = ft_strndup(line + comma[0] + 1, comma[1] - comma[0] - 1);
	s[B] = ft_strndup(line + comma[1] + 1, (ft_strlen(line) - 2) - comma[1]);
	s[3] = NULL;
	return (s);
}

static int	*get_color2(char *line, int *rgb)
{
	int		i;
	char	**s;

	i = -1;
	if (ft_is_in_charcount(line, ',') != 2)
		return (print_error("Invalid color format"), free(rgb),
				NULL);
	while (line[++i])
	{
		s = rgb_split(line);
		if (!s[R] || !s[G] || !s[B] || s[3]
			|| ft_strnstr(line, ",,", ft_strlen(line)))
			return (print_error("Invalid color format"), free(rgb),
				ft_free_lines(s), NULL);
		if (!ft_str_is(ft_isdigit, s[R]) || !ft_str_is(ft_isdigit, s[G])
			|| !ft_str_is(ft_isdigit, s[B]))
			return (print_error("Invalid color value"), free(rgb),
				ft_free_lines(s), NULL);
		strarr_to_intarr(s, rgb);
		if (rgb[R] < 0 || rgb[R] > 255 || rgb[G] < 0 || rgb[G] > 255
			|| rgb[B] < 0 || rgb[B] > 255)
			return (print_error("Invalid color range\n0-255 is valid"),
				free(rgb), NULL);
	}
	return (rgb);
}

static int	*get_color(char letter, char *arg)
{
	int		fd;
	int		*rgb;
	char	*line;
	bool	color_found;

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
			break ;
		if (line[0] == letter && line[1] == ' ' && ft_isdigit(line[2]))
			if (!get_color2(line, rgb))
				return (free(line), close(fd), NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), close(fd), rgb);
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
