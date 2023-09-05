/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:18:45 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/05 17:59:47 by gfranque         ###   ########.fr       */
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
