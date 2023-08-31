/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:20 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/31 17:09:59 by julmuntz         ###   ########.fr       */
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
		cub_clear(game);
		game_clear(game);
		exit(0);
	}
	if (keysym < 127)
		g->key[keysym] = 1;
	/*if (keysym == 65362)
		g->key['w'] = 1;
	else if (keysym == 65364)
		g->key['s'] = 1;*/
	if (keysym == 65361)
		g->key['q'] = 1;
	else if (keysym == 65363)
		g->key['e'] = 1;
	/*if (keysym >= 127)
		printf("key press %d\n", keysym);*/
	return (0);
}

int	ft_key_release(int keysym, void *game)
{
	t_pge	*g;

	g = (t_pge *)game;
	if (keysym < 127)
		g->key[keysym] = 0;
	/*if (keysym == 65362)
		g->key['w'] = 0;
	else if (keysym == 65364)
		g->key['s'] = 0;*/
	if (keysym == 65361)
		g->key['q'] = 0;
	else if (keysym == 65363)
		g->key['e'] = 0;
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
		if (game->cub->map)
			ft_free_lines(game->cub->map);
		free(game->cub);
	}
	if (game->player)
		free(game->player);
}
