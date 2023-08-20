/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:25:37 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/20 17:38:03 by julmuntz         ###   ########.fr       */
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
	int		y;

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
				rgb[R] = ft_atoi(s_rgb[R]);
				rgb[G] = ft_atoi(s_rgb[G]);
				rgb[B] = ft_atoi(s_rgb[B]);
				y = 0;
				while (s_rgb[y])
				{
					free(s_rgb[y]);
					y++;
				}
				free(s_rgb);
				i++;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rgb);
}

int	init_colors(t_config *config, char *arg)
{
	config->ceiling_color = get_color('C', arg);
	config->floor_color = get_color('F', arg);
	return (0);
}

int	rgb_to_hex(int *rgb)
{
	return (((rgb[R] & 0xff) << 16) + ((rgb[G] & 0xff) << 8) + (rgb[B] & 0xff));
}
