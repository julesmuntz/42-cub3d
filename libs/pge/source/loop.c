/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:46 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/21 15:20:27 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

int	ft_loop(t_pge *game)
{
	(void)game;
	return (0);
}

static int	ft_quit(t_pge *game)
{
	free_xpm(game->xpm, game);
	cub_clear(game);
	game_clear(game);
	exit(0);
	return (0);
}

int	mouse_click(int button, int x, int y, t_pge *game)
{
	(void)x;
	(void)y;
	if (game->portal != NULL)
	{
		if (button == 1)
		{
			game->portal->blue_led = true;
			game->portal->orange_led = false;
			game->portal->portal = 1;
			game->portal->laserbeam = true;
		}
		if (button == 3)
		{
			game->portal->blue_led = false;
			game->portal->orange_led = true;
			game->portal->portal = 2;
			game->portal->laserbeam = true;
		}
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_pge *game)
{
	(void)x;
	(void)y;
	if (game->portal != NULL)
	{
		if (button == 1)
			game->portal->laserbeam = false;
		if (button == 3)
			game->portal->laserbeam = false;
	}
	return (0);
}

void	game_loop(t_pge *game, int f(void *))
{
	mlx_loop_hook(game->ptr_mlx, f, game);
	mlx_hook(game->ptr_window, KeyPress, KeyPressMask, &ft_key_press,
		(void *)game);
	mlx_hook(game->ptr_window, KeyRelease, KeyReleaseMask, &ft_key_release,
		(void *)game);
	if (game->portal != NULL)
		mlx_hook(game->ptr_window, MotionNotify, PointerMotionMask,
			&ft_mouse_move, (void *)game);
	mlx_mouse_hook(game->ptr_window, ButtonPress, ButtonPressMask,
		mouse_click, (void *)game);
	mlx_mouse_hook(game->ptr_window, ButtonRelease, ButtonReleaseMask,
		mouse_release, (void *)game);
	mlx_hook(game->ptr_window, ClientMessage, 0, &ft_quit, (void *)game);
	mlx_loop(game->ptr_mlx);
	return ;
}
