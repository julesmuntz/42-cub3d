/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:18:45 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/15 20:40:34 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_xpmpath(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("\033[0;31mError\nFailed to load\n\"%s\"\n\033[0;0m",
				path), 1);
	close(fd);
	return (0);
}

t_portal	*init_portal(void)
{
	t_portal	*portal;

	portal = malloc(sizeof(t_portal));
	if (!portal)
		return (NULL);
	if (check_xpmpath("./assets/portal_entities/crosshair_blue_full.xpm")
		|| check_xpmpath("./assets/portal_entities/crosshair_empty.xpm")
		|| check_xpmpath("./assets/portal_entities/crosshair_full.xpm")
		|| check_xpmpath("./assets/portal_entities/crosshair_orange_full.xpm")
		|| check_xpmpath("./assets/portal_entities/portal_gun_blue.xpm")
		|| check_xpmpath("./assets/portal_entities/portal_gun_orange.xpm")
		|| check_xpmpath("./assets/portal_entities/portal_gun.xpm"))
		return (free(portal), NULL);
	portal->clicked_blue = false;
	portal->clicked_orange = false;
	portal->blue_led = false;
	portal->orange_led = false;
	portal->laserbeam = false;
	portal->portal = 0;
	portal->portalgun_ent_path = "./assets/portal_entities/portal_gun.xpm";
	portal->crosshair_ent_path = "./assets/portal_entities/crosshair_empty.xpm";
	return (portal);
}

void	refresh_portal_colors(t_pge *game)
{
	if (game->portal->blue_led == true && game->portal->orange_led == false)
		game->portal->portalgun_ent_path
			= "./assets/portal_entities/portal_gun_blue.xpm";
	if (game->portal->blue_led == false && game->portal->orange_led == true)
		game->portal->portalgun_ent_path
			= "./assets/portal_entities/portal_gun_orange.xpm";
	if (game->portal->clicked_blue == true
		&& game->portal->clicked_orange == false)
		game->portal->crosshair_ent_path
			= "./assets/portal_entities/crosshair_blue_full.xpm";
	if (game->portal->clicked_blue == false
		&& game->portal->clicked_orange == true)
		game->portal->crosshair_ent_path
			= "./assets/portal_entities/crosshair_orange_full.xpm";
	if (game->portal->clicked_blue == true
		&& game->portal->clicked_orange == true)
		game->portal->crosshair_ent_path
			= "./assets/portal_entities/crosshair_full.xpm";
}

static void	add_laser(t_pge *game, int shift[2],
	t_pxl blue_laser, t_pxl orange_laser)
{
	t_vi	coor;
	t_vi	size;
	t_pxl	pixel;

	coor = set_vector(game->drawing_img.width / 2 + shift[0],
			game->drawing_img.height / 2 + shift[1]);
	size = set_vector(game->drawing_img.width / 7.5,
			game->drawing_img.height / 4);
	if (game->portal->blue_led == true && game->portal->laserbeam == true)
		pixel = blue_laser;
	else if (game->portal->orange_led == true
		&& game->portal->laserbeam == true)
		pixel = orange_laser;
	else
		pixel = set_pxl_argb(255, 255, 255, 255);
	draw_line(&coor, &size, game, &pixel);
}

void	print_laserbeam(t_pge *game)
{
	add_laser(game, (int [2]){0, 0}, set_pxl_argb(173, 221, 255, 0),
		set_pxl_argb(255, 210, 128, 0));
	add_laser(game, (int [2]){1, 0}, set_pxl_argb(121, 199, 255, 0),
		set_pxl_argb(255, 200, 99, 0));
	add_laser(game, (int [2]){0, 1}, set_pxl_argb(121, 199, 255, 0),
		set_pxl_argb(255, 200, 99, 0));
	add_laser(game, (int [2]){2, 0}, set_pxl_argb(80, 181, 255, 0),
		set_pxl_argb(255, 188, 65, 0));
	add_laser(game, (int [2]){0, 2}, set_pxl_argb(80, 181, 255, 0),
		set_pxl_argb(255, 188, 65, 0));
}
