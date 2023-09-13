/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:36:52 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/13 16:34:08 by gfranque         ###   ########.fr       */
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

int	ft_is_in_charcount(char *str, char tofind)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!str)
		return (i);
	while (str[i])
	{
		if (str[i] == tofind)
			n++;
		i++;
	}
	return (n);
}
