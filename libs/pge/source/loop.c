/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:46 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/21 16:49:02 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

int	ft_loop(t_pge *game)
{
	(void)game;
	return (0);
}

void	game_loop(t_pge *game)
{
	game_refresh(game);
	mlx_loop_hook(game->ptr_mlx, &ft_loop, NULL);
	mlx_hook(game->ptr_window, KeyPress, KeyPressMask,
		&ft_key_press, (void *)game);
	mlx_hook(game->ptr_window, KeyRelease, KeyReleaseMask,
		&ft_key_release, (void *)game);
	mlx_loop(game->ptr_mlx);
	return ;
}
