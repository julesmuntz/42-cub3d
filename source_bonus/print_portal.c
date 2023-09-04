/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:17:21 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/04 17:51:02 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_portal_gun(t_pge *game)
{
	t_vi	coor;
	t_vi	size;
	t_xpm	*sprite;

	coor = set_vector(game->drawing_img.width / 2, game->drawing_img.height
			/ 2);
	size = copy_vector(&coor);
	if (game->portal->blue_led == true)
		sprite = find_xpm(game->xpm, "bluegun");
	else if (game->portal->orange_led == true)
		sprite = find_xpm(game->xpm, "orangegun");
	else
		sprite = find_xpm(game->xpm, "gun");
	if (sprite)
		print_sprite(sprite, coor, size, game);
}

void	print_crosshair(t_pge *game)
{
	t_vi	coor;
	t_vi	size;
	t_xpm	*sprite;

	coor = set_vector(game->drawing_img.width / 2 - game->drawing_img.width
			/ 28, game->drawing_img.height / 2 - game->drawing_img.width / 28);
	size = set_vector(game->drawing_img.width / 14, game->drawing_img.width
			/ 14);
	if (game->portal->clicked_blue == true)
	{
		if (game->portal->clicked_orange == true)
			sprite = find_xpm(game->xpm, "crosshairfull");
		else
			sprite = find_xpm(game->xpm, "crosshairblue");
	}
	else if (game->portal->clicked_orange == true)
		sprite = find_xpm(game->xpm, "crosshairorange");
	else
		sprite = find_xpm(game->xpm, "crosshair");
	if (sprite)
		print_sprite(sprite, coor, size, game);
}

int	add_portal_texture(t_pge *game)
{
	game->xpm = game_add_xpm("./assets/portal_entities/portal_gun_blue.xpm",
			"bluegun", game->xpm, game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm("./assets/portal_entities/portal_gun_orange.xpm",
			"orangegun", game->xpm, game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm("./assets/portal_entities/crosshair_full.xpm",
			"crosshairfull", game->xpm, game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm("./assets/portal_entities/crosshair_blue_full.xpm",
			"crosshairblue", game->xpm, game);
	if (!game->xpm)
		return (0);
	game->xpm = game_add_xpm(
			"./assets/portal_entities/crosshair_orange_full.xpm",
			"crosshairorange", game->xpm, game);
	if (!game->xpm)
		return (0);
	return (1);
}
