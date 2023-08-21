/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:25:37 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/21 17:29:27 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	xpm_color(t_mlx *mlx, float x, float y)
{
	int			pixelx;
	int			pixely;
	int const	*addresse;

	pixelx = mlx->wall.width * x;
	pixely = mlx->wall.height * y;
	addresse = (int *)mlx->wall.addr;
	return (addresse[mlx->wall.width * pixely + pixelx]);
}

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
	i = 0;
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
			color_found = true;
			while (line[i])
			{
				s_rgb = ft_split(line + 2, ',');
				if (!s_rgb[R] || !s_rgb[G] || !s_rgb[B] || s_rgb[3])
					return (printf("%sError\nInvalid color format (%c)\n%s", RED, letter, NONE),
						free(rgb), ft_free_lines(s_rgb), free(line), close(fd), NULL);
				rgb[R] = ft_atoi(s_rgb[R]);
				rgb[G] = ft_atoi(s_rgb[G]);
				rgb[B] = ft_atoi(s_rgb[B]);
				ft_free_lines(s_rgb);
				if (rgb[R] < 0 || rgb[R] > 255 || rgb[G] < 0 || rgb[G] > 255
					|| rgb[B] < 0 || rgb[B] > 255)
					return (printf("%sError\nInvalid color range (%c)\n0-255 is valid\n%s", RED, letter, NONE),
						free(rgb), free(line), close(fd), NULL);
				i++;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rgb);
}

int	init_colors(t_cub *cub, char *arg)
{
	cub->ceiling_color = get_color('C', arg);
	if (!cub->ceiling_color)
		return (1);
	cub->floor_color = get_color('F', arg);
	if (!cub->floor_color)
		return (1);
	return (0);
}

int	rgb_to_hex(int *rgb)
{
	return (((rgb[R] & 0xff) << 16) + ((rgb[G] & 0xff) << 8) + (rgb[B] & 0xff));
}
