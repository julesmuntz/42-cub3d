/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:43:12 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/04 16:42:12 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_direction(t_pge *game, float n)
{
	game->player->angle -= n;
	vectorf_rotation(&game->player->dir, n);
	vectorf_rotation(&game->player->plan, n);
}

bool	check_collision(t_pge *game)
{
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x + 0.1f)] == '1')
		return (1);
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x - 0.1f)] == '1')
		return (1);
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x - 0.1f)] == '1')
		return (1);
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x + 0.1f)] == '1')
		return (1);
	return (0);
}
