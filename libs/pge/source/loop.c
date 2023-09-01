/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:46 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/01 14:17:53 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

int	ft_loop(t_pge *game)
{
	(void)game;
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
	mlx_loop(game->ptr_mlx);
	return ;
}
