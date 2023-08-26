/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:20 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/26 14:43:06 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

int	ft_key_press(int keysym, void *game)
{
	t_pge	*g;

	g = (t_pge *)game;
	if (keysym == XK_Escape)
	{
		free_xpm(g->xpm, game);
		printf("cub clear\n");
		cub_clear(game);
		game_clear(game);
		exit(0);
	}
	if (keysym < 127)
		g->key[keysym] = 1;
	printf("key press %d\n", keysym);
	return (0);
}

int	ft_key_release(int keysym, void *game)
{
	t_pge	*g;

	g = (t_pge *)game;
	if (keysym < 127)
		g->key[keysym] = 0;
	return (0);
}

void	cub_clear(t_pge *game)
{
	if (game->cub)
	{
		free(game->cub->north_tex_path);
		free(game->cub->south_tex_path);
		free(game->cub->west_tex_path);
		free(game->cub->east_tex_path);
		free(game->cub->floor_color);
		free(game->cub->ceiling_color);
		ft_free_lines(game->cub->map);
		free(game->cub);
	}
	if (game->player)
		free(game->player);
}
