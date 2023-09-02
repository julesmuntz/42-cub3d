/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:46 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/02 19:30:32 by julmuntz         ###   ########.fr       */
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
	if (button == 1)
	{
		game->portal->blue_led = true;
		game->portal->orange_led = false;
		game->portal->clicked_blue = true;
	}
	if (button == 3)
	{
		game->portal->blue_led = false;
		game->portal->orange_led = true;
		game->portal->clicked_orange = true;
	}

	//temp
	ft_putstr("\n");
	if (game->portal->blue_led == true && game->portal->orange_led == false)
		ft_putstr("\1\033[38;5;033m\2The led is blue\n\1\033[0m\2");
	if (game->portal->blue_led == false && game->portal->orange_led == true)
		ft_putstr("\1\033[38;5;208m\2The led is orange\n\1\033[0m\2");
	if (game->portal->clicked_blue == true && game->portal->clicked_orange == false)
		ft_putstr("\1\033[38;5;033m\2The blue part of the crosshair is filled\n\1\033[0m\2");
	if (game->portal->clicked_blue == false && game->portal->clicked_orange == true)
		ft_putstr("\1\033[38;5;208m\2The orange part of the crosshair is filled\n\1\033[0m\2");
	if (game->portal->clicked_blue == true && game->portal->clicked_orange == true)
		ft_putstr("\1\033[38;5;159m\2Both parts of the crosshair are filled\n\1\033[0m\2");
	//temp

	return (0);
}

void	game_loop(t_pge *game, int f(void *))
{
	mlx_loop_hook(game->ptr_mlx, f, game);
	mlx_hook(game->ptr_window, KeyPress, KeyPressMask,
		&ft_key_press, (void *)game);
	mlx_hook(game->ptr_window, KeyRelease, KeyReleaseMask,
		&ft_key_release, (void *)game);
	mlx_hook(game->ptr_window, MotionNotify, PointerMotionMask,
		&ft_mouse_move, (void *)game);
	mlx_mouse_hook(game->ptr_window, mouse_click, (void *)game);
	mlx_hook(game->ptr_window, ClientMessage, 0, &ft_quit, (void *)game);
	mlx_loop(game->ptr_mlx);
	return ;
}
