/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:55:33 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/28 18:13:11 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_fov(float const fov, t_player *player)
{
	player->plan.y = vectorf_dist(&player->dir) * tanf(fov / 2);
}

t_player	*set_player(t_vi const *pos, float const playera, float const fov)
{
	t_player	*player;

	player = malloc(sizeof(t_player) * 1);
	if (!player)
		return (NULL);
	player->pos = set_vectorf((float)pos->x + 0.5f, (float)pos->y + 0.5f);
	player->dir = set_vectorf(1.0f, 0.0f);
	player->plan = set_vectorf(0.0f, 1.0f);
	// player->angle = playera;
	player->angle = -M_PI_2;
	(void)playera;
	set_fov(fov, player);
	return (player);
}
