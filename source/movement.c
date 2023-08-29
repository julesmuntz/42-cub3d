/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:36:57 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/29 17:33:02 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_right(t_pge *game, float n)
{
	float	cos;
	float	sin;

	cos = cosf(game->player->angle) * n;
	sin = sinf(game->player->angle) * n;
	game->player->pos.x += cos;
	game->player->pos.y -= sin;
	if (check_collision(game) == 1)
	{
		game->player->pos.x -= cos;
		game->player->pos.y += sin;
	}
}

void	go_left(t_pge *game, float n)
{
	float	cos;
	float	sin;

	cos = cosf(game->player->angle) * n;
	sin = sinf(game->player->angle) * n;
	game->player->pos.x -= cos;
	game->player->pos.y += sin;
	if (check_collision(game) == 1)
	{
		game->player->pos.x += cos;
		game->player->pos.y -= sin;
	}
}

void	go_front(t_pge *game, float n)
{
	float	sin;
	float	cos;

	sin = sinf(game->player->angle) * n;
	cos = cosf(game->player->angle) * n;
	game->player->pos.x -= sin;
	game->player->pos.y -= cos;
	if (check_collision(game) == 1)
	{
		game->player->pos.x += sin;
		game->player->pos.y += cos;
	}
}

void	go_back(t_pge *game, float n)
{
	float	sin;
	float	cos;

	sin = sinf(game->player->angle) * n;
	cos = cosf(game->player->angle) * n;
	game->player->pos.x += sin;
	game->player->pos.y += cos;
	if (check_collision(game) == 1)
	{
		game->player->pos.x -= sin;
		game->player->pos.y -= cos;
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
