/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:09:13 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/05 17:36:41 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *str)
{
	write(STDERR_FILENO, "\033[0;31mError\n", 13);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n\033[0;0m", 7);
}

bool	invalid_extension(char *filename)
{
	char	*cub;

	if (!filename)
		return (true);
	cub = ft_strrchr(filename, '.');
	if (!cub || ft_strncmp(cub, ".cub\0", 5))
		return (true);
	return (false);
}

void	calculate_map_dimensions(t_pge *game, int fd)
{
	char	*line;
	int		row_length;
	int		sp;

	line = get_next_line(fd);
	while (line)
	{
		sp = 0;
		while (ft_isspace(line[sp]))
			sp++;
		if (ft_ismap_char(line[sp]))
		{
			row_length = sp;
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

void	flood_fill(t_pge *game, int a, int b, bool *failure)
{
	if (a < 0 || b < 0 || a >= game->cub->map_height || !game->cub->map[a]
		|| !game->cub->map[a][b])
	{
		*failure = true;
		return ;
	}
	if (game->cub->map[a][b] == '1' || game->cub->map[a][b] == 'X')
		return ;
	game->cub->map[a][b] = 'X';
	flood_fill(game, a + 1, b, failure);
	flood_fill(game, a - 1, b, failure);
	flood_fill(game, a, b + 1, failure);
	flood_fill(game, a, b - 1, failure);
}

int	door_is_close(t_pge *game, int x, int y)
{
	if (game->player->pos.x >= x - 0.5f && game->player->pos.x <= x + 1.5f
		&& game->player->pos.y >= y - 0.5f && game->player->pos.y <= y + 1.5f)
		return (0);
	return (1);
}
