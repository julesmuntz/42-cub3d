/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:17:21 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/15 11:35:01 by julmuntz         ###   ########.fr       */
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

int	add_door_texture(t_pge *game)
{
	game->xpm = game_add_xpm("assets/portal_textures/door.xpm",
			"door", game->xpm, game);
	if (!game->xpm)
		return (print_error("door xpm failed to load\n"), 0);
	return (1);
}

int	add_portal_text(t_pge *game)
{
	game->xpm = game_add_xpm("./assets/portal_textures/portal_blue.xpm",
			"portalb", game->xpm, game);
	if (!game->xpm)
		return (print_error("portal blue xpm failed to load\n"), 0);
	game->xpm = game_add_xpm("./assets/portal_textures/portal_orange.xpm",
			"portalo", game->xpm, game);
	if (!game->xpm)
		return (print_error("portal orange xpm failed to load\n"), 0);
	return (1);
}

int	add_portal_texture(t_pge *game)
{
	if (add_door_texture(game) == 0)
		return (0);
	game->xpm = game_add_xpm("./assets/portal_entities/portal_gun_blue.xpm",
			"bluegun", game->xpm, game);
	if (!game->xpm)
		return (print_error("portalgun (blue led) xpm failed to load\n"), 0);
	game->xpm = game_add_xpm("./assets/portal_entities/portal_gun_orange.xpm",
			"orangegun", game->xpm, game);
	if (!game->xpm)
		return (print_error("portalgun (orange led) xpm failed to load\n"), 0);
	game->xpm = game_add_xpm("./assets/portal_entities/crosshair_full.xpm",
			"crosshairfull", game->xpm, game);
	if (!game->xpm)
		return (print_error("crosshair (full) xpm failed to load\n"), 0);
	game->xpm = game_add_xpm("./assets/portal_entities/crosshair_blue_full.xpm",
			"crosshairblue", game->xpm, game);
	if (!game->xpm)
		return (print_error("crosshair (blue) xpm failed to load\n"), 0);
	game->xpm = game_add_xpm(
			"./assets/portal_entities/crosshair_orange_full.xpm",
			"crosshairorange", game->xpm, game);
	if (!game->xpm)
		return (print_error("crosshair (orange) xpm failed to load\n"), 0);
	return (add_portal_text(game));
}
