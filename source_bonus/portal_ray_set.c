/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_ray_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:25:14 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/20 20:19:03 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*

le rayon touche un portail:
on obtient la coordonnee du point d'impacte
en fonction de son orientation, il faut recuperer le x ou le y - sa valeur en int
recuperer le x et le y et les soustraires avec leur valeur en int (plus simple)

la nouvelle coordonnee du rayon:
en fonction de l'orientation du portail
N -> portail.x du portail + x + y (du point d'impact); portail.y (rien ne change)
S -> portail.x du portail + x + y (du point d'impact); portail.y + 1
W -> portail.x (rien ne change); portail.y du portail + x + y (du point d'impact)
E -> portail.x + 1; portail portail.y = portail.y + x + y (du point d'impact)

remplacer x et y par wallx (deja calcule)

la nouvelle direction du rayon:
fonction qui "calcul le nombre de rotations"
quatre cas:
un sur la gauche
	(P.y;-P.x)
deux sur la gauche
	(P.x;P.y)
trois sur la gauche
	(-P.y;P.x)
quatrieme sur la gauche
	(-P.x;-P.y)

*/

char	collition_in_portal(t_pge *game)
{
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x + 0.1f)] == 'B')
		return ('B');
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x - 0.1f)] == 'B')
		return ('B');
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x - 0.1f)] == 'B')
		return ('B');
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x + 0.1f)] == 'B')
		return ('B');
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x + 0.1f)] == 'O')
		return ('O');
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x - 0.1f)] == 'O')
		return ('O');
	if (game->cub->map[(int)(game->player->pos.y
			+ 0.1f)][(int)(game->player->pos.x - 0.1f)] == 'O')
		return ('O');
	if (game->cub->map[(int)(game->player->pos.y
			- 0.1f)][(int)(game->player->pos.x + 0.1f)] == 'O')
		return ('O');
	return ('P');
}

void	teleport_rotation(t_pge *game, char dir)
{
	if (dir == 'N' && game->player->p == 'N')
		look_direction(game, M_PI);
	else if (dir == 'N' && game->player->p == 'E')
		look_direction(game, M_PI_2);
	else if (dir == 'N' && game->player->p == 'W')
		look_direction(game, -M_PI_2);
	else if (dir == 'E' && game->player->p == 'E')
		look_direction(game, M_PI);
	else if (dir == 'E' && game->player->p == 'S')
		look_direction(game, M_PI_2);
	else if (dir == 'E' && game->player->p == 'N')
		look_direction(game, -M_PI_2);
	else if (dir == 'W' && game->player->p == 'W')
		look_direction(game, M_PI);
	else if (dir == 'W' && game->player->p == 'N')
		look_direction(game, M_PI_2);
	else if (dir == 'W' && game->player->p == 'S')
		look_direction(game, -M_PI_2);
	else if (dir == 'S' && game->player->p == 'S')
		look_direction(game, M_PI);
	else if (dir == 'S' && game->player->p == 'W')
		look_direction(game, M_PI_2);
	else if (dir == 'S' && game->player->p == 'E')
		look_direction(game, -M_PI_2);
}

char	check_pos_side(t_pge *game)
{
	if ((int)game->player->oldpos.x < (int)game->player->pos.x)
		game->player->p = 'E';
	else if ((int)game->player->oldpos.x > (int)game->player->pos.x)
		game->player->p = 'W';
	else if ((int)game->player->oldpos.y < (int)game->player->pos.y)
		game->player->p = 'S';
	else if ((int)game->player->oldpos.y > (int)game->player->pos.y)
		game->player->p = 'N';
	return (game->player->p);
}
