/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:06:40 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/11 15:14:18 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

int	game_open_window(t_pge *game, char const *name)
{
	game->ptr_window = mlx_new_window(game->ptr_mlx, game->width, game->height,
			(char *)name);
	if (!game->ptr_window)
	{
		game_clear(game);
		return (0);
	}
	return (1);
}
