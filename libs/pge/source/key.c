/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:20 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/21 16:48:06 by gfranque         ###   ########.fr       */
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
