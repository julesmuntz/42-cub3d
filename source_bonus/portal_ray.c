/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:51:36 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/20 16:14:26 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_portal(t_pge *game, t_raycast *ray, float walldist, char dir)
{
	t_vf		start;
	t_raycast	*rcast;

	rcast = malloc(sizeof(t_raycast));
	if (!rcast)
	{
		free_xpm(game->xpm, game);
		cub_clear(game);
		game_clear(game);
		exit(2);
	}
	*rcast = *ray;
	start = set_portal_value(game, rcast, dir);
	printf("===============\nplayer[%f;%f]\nwalldist[%f]\ndeltadist[%f;%f]\n", game->player->pos.x, game->player->pos.y, rcast->walldist, rcast->deltadist.x, rcast->deltadist.y);
	rcast->deltadist.x = fabsf(1.f / rcast->raydir.x);
	rcast->deltadist.y = fabsf(1.f / rcast->raydir.y);
	rcast->hit = 0;
	(void)walldist;
	// rcast->walldist += walldist;
	ray->map.x = start.x;
	ray->map.y = start.y;
	printf("===============\nstart[%f;%f]\nwalldist[%f]\ndeltadist[%f;%f]\n\n", start.x, start.y, rcast->walldist, rcast->deltadist.x, rcast->deltadist.y);
	raycast_dda(game, rcast, &start, &game->drawing_img);
	free(rcast);
}

char	get_side(t_raycast	*ray)
{
	if (ray->side == 0)
	{
		if (ray->step.x < 0)
			return ('W');
		else
			return ('E');
	}
	else if (ray->side == 1)
	{
		if (ray->step.y < 0)
			return ('N');
		else
			return ('S');
	}
	return (0);
}

int	check_side(t_pge *game, t_raycast *ray, char p)
{
	if (p == 'B')
	{
		if (game->player->pb == get_side(ray))
		{
			printf("est sur le meme side\n");
			return (1);
		}
		return (0);
	}
	if (p == 'O')
	{
		if (game->player->po == get_side(ray))
		{
			printf("est sur le meme side\n");
			return (1);
		}
		return (0);
	}
	return (0);
}
