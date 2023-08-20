/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:16:08 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/20 17:35:30 by julmuntz         ###   ########.fr       */
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
			return (path);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (NULL);
}

static void	exit_program(t_mlx *mlx, t_config *config)
{
	mlx_destroy_image(mlx->ptr_mlx, mlx->img.mlx_img);
	mlx_destroy_window(mlx->ptr_mlx, mlx->ptr_window);
	mlx_destroy_display(mlx->ptr_mlx);
	ft_free_lines(g_map);
	free(config->north_texture);
	free(config->south_texture);
	free(config->west_texture);
	free(config->east_texture);
	free(mlx->ptr_mlx);
	exit(0);
}

static bool	valid_texture(char *tex_path)
{
	int	fd;

	fd = open(tex_path, O_RDONLY);
	if (fd == -1)
		return (printf("%sError\nFailed to load \"%s\"\n%s",
				RED, tex_path, NONE), false);
	return (true);
}

int	init_textures(t_mlx *mlx, t_config *config, char *arg)
{
	bool	failure;

	failure = false;
	config->north_texture = get_texture_path("NO", arg);
	if (!valid_texture(config->north_texture))
		failure = true;
	config->south_texture = get_texture_path("SO", arg);
	if (!valid_texture(config->south_texture))
		failure = true;
	config->west_texture = get_texture_path("WE", arg);
	if (!valid_texture(config->west_texture))
		failure = true;
	config->east_texture = get_texture_path("EA", arg);
	if (!valid_texture(config->east_texture))
		failure = true;
	if (failure == true)
		exit_program(mlx, config);
	return (0);
}

int	set_texture_to_walls(char *tex_path, t_mlx *mlx, t_config *config)
{
	mlx->wall.mlx_img = mlx_xpm_file_to_image(mlx->ptr_mlx, tex_path,
			&mlx->wall.width, &mlx->wall.height);
	free(config->north_texture);
	free(config->south_texture);
	free(config->west_texture);
	free(config->east_texture);
	if (mlx->wall.mlx_img == NULL)
	{
		mlx_destroy_image(mlx->ptr_mlx, mlx->img.mlx_img);
		mlx_destroy_window(mlx->ptr_mlx, mlx->ptr_window);
		mlx_destroy_display(mlx->ptr_mlx);
		ft_free_lines(g_map);
		free(mlx->ptr_mlx);
		exit(0);
	}
	return (0);
}
