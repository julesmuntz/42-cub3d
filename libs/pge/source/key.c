/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:20 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/01 17:32:44 by julmuntz         ###   ########.fr       */
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
	if (keysym == XK_Left)
		g->key['q'] = 1;
	if (keysym == XK_Right)
		g->key['e'] = 1;
	if (keysym == XK_Up)
		g->key[1] = 1;
	if (keysym == XK_Down)
		g->key[2] = 1;
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
	else if (keysym == XK_Up)
		g->key[1] = 0;
	else if (keysym == XK_Down)
		g->key[2] = 0;
	return (0);
}

static void	look_direction(t_pge *game, float n)
{
	game->player->angle -= n;
	vectorf_rotation(&game->player->dir, n);
	vectorf_rotation(&game->player->plan, n);
}

int	ft_mouse_move(int x, int y, void *game)
{
	t_pge	*g;
	int		last_x;
	int		last_y;
	float	delta_x;
	float	delta_y;

	g = (t_pge *)game;
	last_x = g->width / 2;
	last_y = g->height / 2;
	delta_x = x - last_x;
	delta_y = y - last_y;
	if (delta_x > 0)
		look_direction(g, delta_x * 0.001f);
	else if (delta_x < 0)
		look_direction(g, delta_x * 0.001f);
	g->player->pitch = fmax(fmin(g->player->pitch - delta_y * 0.0075f,
				10.0f), -10.0f);
	mlx_mouse_move(g->ptr_mlx, g->ptr_window, g->width / 2, g->height / 2);
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
