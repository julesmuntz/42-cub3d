/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:36:57 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/28 17:11:32 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_right(t_pge *game, float n)
{
	game->player->pos.x += cosf(game->player->angle) * n;
	game->player->pos.y -= sinf(game->player->angle) * n;
	if (game->cub->map[(int)game->player->pos.y][(int)game->player->pos.x]
			== '1')
	{
		game->player->pos.x -= cosf(game->player->angle) * n;
		game->player->pos.y += sinf(game->player->angle) * n;
	}
}

void	go_left(t_pge *game, float n)
{
	game->player->pos.x -= cosf(game->player->angle) * n;
	game->player->pos.y += sinf(game->player->angle) * n;
	if (game->cub->map[(int)game->player->pos.y][(int)game->player->pos.x]
			== '1')
	{
		game->player->pos.x += cosf(game->player->angle) * n;
		game->player->pos.y -= sinf(game->player->angle) * n;
	}
}

void	go_front(t_pge *game, float n)
{
	game->player->pos.x -= sinf(game->player->angle) * n;
	game->player->pos.y -= cosf(game->player->angle) * n;
	if (game->cub->map[(int)game->player->pos.y][(int)game->player->pos.x]
			== '1')
	{
		game->player->pos.x += sinf(game->player->angle) * n;
		game->player->pos.y += cosf(game->player->angle) * n;
	}
}

void	go_back(t_pge *game, float n)
{
	game->player->pos.x += sinf(game->player->angle) * n;
	game->player->pos.y += cosf(game->player->angle) * n;
	if (game->cub->map[(int)game->player->pos.y][(int)game->player->pos.x]
			== '1')
	{
		game->player->pos.x -= sinf(game->player->angle) * n;
		game->player->pos.y -= cosf(game->player->angle) * n;
	}
}

void	check_movements(t_pge *game)
{
	float	speed;
	float	look;

	speed = 0.1f;
	look = 0.06f;
	if (game->key['w'] == 1)
		go_front(game, speed);
	if (game->key['s'] == 1)
		go_back(game, speed);
	if (game->key['a'] == 1)
		go_left(game, speed);
	if (game->key['d'] == 1)
		go_right(game, speed);
	if (game->key['q'] == 1)
		look_direction(game, -look);
	if (game->key['e'] == 1)
		look_direction(game, look);
}
