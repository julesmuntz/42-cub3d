/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:35:48 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/21 14:54:20 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_pge *game, t_xpm *sprite)
{
	t_pxl	pxl;
	t_vi	coor;
	t_vi	size;

	pxl = set_pxl_argb(game->cub->floor_color[R], game->cub->floor_color[G],
			game->cub->floor_color[B], 0);
	coor = set_vector(sprite->width / 2, sprite->height / 2);
	fill_circle_xpm(&coor, sprite->height / 2, sprite, &pxl);
	pxl = set_pxl_argb(13, 224, 56, 0);
	fill_circle_xpm(&coor, 4, sprite, &pxl);
}

/*print le personnage a la fin !*/
/*pour l'instant, le cercle est de la couleur du sol
et le cercle du perso est sur le centre de la sprite*/

void	refresh_minimap(t_pge *game)
{
	int		i;
	t_xpm	**sprite;

	sprite = game->xpm;
	i = 0;
	while (sprite[i])
	{
		if (ft_strlen(sprite[i]->name) == 5 && ft_strncmp(sprite[i]->name,
				"mnmap", 5) == 0)
			break ;
		i++;
	}
	if (sprite[i] == NULL)
		return ;
	draw_minimap(game, sprite[i]);
}

void	minimap_put_wall(t_pge *game, t_xpm *sprite, int r, t_pxl *pxl)
{
	t_vi	coor;
	t_vi	delta;
	t_vi	xy;
	t_vi	size_rec;

	size_rec = set_vector(sprite->width / 6, sprite->height / 6);
	coor.x = (game->player->pos.x - (int)(game->player->pos.x) * 10) * -1;
	coor.y = (game->player->pos.y - (int)(game->player->pos.y) * 10) * -1;
	xy.y = (int)(game->player->pos.y) - 3;
	while (coor.y < sprite->height)
	{
		coor.x = 0;
		xy.x = (int)(game->player->pos.x) - 3;
		while (coor.x < sprite->width)
		{
			if (xy.x >= 0 && xy.y >= 0 && xy.x < game->cub->map_width
				&& xy.y < game->cub->map_height)
				fill_rectangle_xpm(&coor, &size_rec, sprite, &pxl);
			xy.x++;
			coor.x += size_rec.x;
		}
		xy.y++;
		coor.y += size_rec.y;
	}
}

/*faire le decoupage circulaire a la fin pour la transparence*/
