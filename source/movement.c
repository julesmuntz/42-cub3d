/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:36:57 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/19 12:50:54 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_front(float n)
{
	g_player_x += sinf(g_player_a) * n;
	g_player_y += cosf(g_player_a) * n;
	if (g_map[(int)g_player_y][(int)g_player_x] == '1')
	{
		g_player_x -= sinf(g_player_a) * n;
		g_player_y -= cosf(g_player_a) * n;
	}
}

void	go_back(float n)
{
	g_player_x -= sinf(g_player_a) * n;
	g_player_y -= cosf(g_player_a) * n;
	if (g_map[(int)g_player_y][(int)g_player_x] == '1')
	{
		g_player_x += sinf(g_player_a) * n;
		g_player_y += cosf(g_player_a) * n;
	}
}

void	go_left(float n)
{
	g_player_x -= cosf(g_player_a) * n;
	g_player_y += sinf(g_player_a) * n;
	if (g_map[(int)g_player_y][(int)g_player_x] == '1')
	{
		g_player_x += cosf(g_player_a) * n;
		g_player_y -= sinf(g_player_a) * n;
	}
}

void	go_right(float n)
{
	g_player_x += cosf(g_player_a) * n;
	g_player_y -= sinf(g_player_a) * n;
	if (g_map[(int)g_player_y][(int)g_player_x] == '1')
	{
		g_player_x -= cosf(g_player_a) * n;
		g_player_y += sinf(g_player_a) * n;
	}
}
