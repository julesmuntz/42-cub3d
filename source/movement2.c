/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:43:12 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/28 17:10:20 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_direction(t_pge *game, float n)
{
	game->player->angle -= n;
	vectorf_rotation(&game->player->dir, n);
	vectorf_rotation(&game->player->plan, n);
}
