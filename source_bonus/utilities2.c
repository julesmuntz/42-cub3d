/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:36:52 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/05 15:37:12 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_door(t_pge *game, int *a, int *b)
{
	if (game->cub->map[*a][*b] == 'D')
		game->cub->door_found = true;
	if (game->cub->map[*a][*b] == 'D'
		&& (!((ft_ismap_walkable(game->cub->map[*a - 1][*b])
		&& ft_ismap_walkable(game->cub->map[*a + 1][*b])
		&& game->cub->map[*a][*b - 1] == '1'
		&& game->cub->map[*a][*b + 1] == '1')
		|| (ft_ismap_walkable(game->cub->map[*a][*b - 1])
		&& ft_ismap_walkable(game->cub->map[*a][*b + 1])
		&& game->cub->map[*a - 1][*b] == '1'
		&& game->cub->map[*a + 1][*b] == '1'))))
		game->cub->invalid_door = true;
}
