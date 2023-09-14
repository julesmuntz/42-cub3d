/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:48:03 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/14 16:23:56 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	portal_orientation(t_pge *game, char *portal)
{
	if (game->player->t == 1)
		*portal = 'E';
	else if (game->player->t == -1)
		*portal = 'W';
	else if (game->player->t == -2)
		*portal = 'N';
	else if (game->player->t == 2)
		*portal = 'S';
}

void	check_portal(t_pge *game)
{
	if (game->portal->portal == 1)
	{
		if (game->cub->map[game->player->target.y][game->player->target.x] == '1')
		{
			game->cub->map[game->player->portalb.y][game->player->portalb.x] = '1';
			game->cub->map[game->player->target.y][game->player->target.x] = 'B';
			game->player->portalb = set_vector(game->player->target.x, game->player->target.y);
			portal_orientation(game, &game->player->pb);
			printf("pos[%d, %d] side [%c]\n", game->player->portalb.x, game->player->portalb.y, game->player->pb);
		}
		game->portal->portal = 0;
	}
	else if (game->portal->portal == 2)
	{
		if (game->cub->map[game->player->target.y][game->player->target.x] == '1')
		{
			game->cub->map[game->player->portalo.y][game->player->portalo.x] = '1';
			game->cub->map[game->player->target.y][game->player->target.x] = 'O';
			game->player->portalo = set_vector(game->player->target.x, game->player->target.y);
			portal_orientation(game, &game->player->po);
			printf("pos[%d, %d] side [%c]\n", game->player->portalo.x, game->player->portalo.y, game->player->po);
		}
		game->portal->portal = 0;
	}
}
