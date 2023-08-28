/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:14 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/28 18:10:18 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

static short int	game_image_add(t_pge *game, t_im *img, short int width,
	short int height)
{
	img->mlx_img = mlx_new_image(game->ptr_mlx, width, height);
	if (!img->mlx_img)
		return (0);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	img->width = width;
	img->height = height;
	return (1);
}

static short int	game_set(t_pge *game, char const *name)
{
	game->ptr_mlx = mlx_init();
	if (!game->ptr_mlx)
	{
		free(game);
		return (0);
	}
	game->ptr_window = mlx_new_window(game->ptr_mlx, game->width, game->height,
			(char *)name);
	if (!game->ptr_window)
	{
		game_clear(game);
		return (0);
	}
	if (game_image_add(game, &game->img, game->width, game->height) == 0)
	{
		game_clear(game);
		return (0);
	}
	if (game_image_add(game, &game->drawing_img, game->width / game->pxlwidth,
			game->height / game->pxlheight) == 0)
	{
		game_clear(game);
		return (0);
	}
	return (1);
}

t_pge	*game_init(t_vi *screensize, t_vi *pxlsize, char const *name)
{
	t_pge	*game;
	int		i;

	game = malloc(sizeof(t_pge) * 1);
	if (!game)
		return (NULL);
	i = -1;
	game->ray = malloc(sizeof(t_raycast));
	if (!game->ray)
		return (free(game), NULL);
	game->width = screensize->x;
	game->height = screensize->y;
	game->pxlwidth = pxlsize->x;
	game->pxlheight = pxlsize->y;
	game->ptr_mlx = NULL;
	game->ptr_window = NULL;
	game->img.mlx_img = NULL;
	game->drawing_img.mlx_img = NULL;
	game->xpm = NULL;
	while (++i < 127)
		game->key[i] = 0;
	if (game_set(game, name) == 1)
		return (game);
	return (NULL);
}

void	game_clear(t_pge *game)
{
	if (game->drawing_img.mlx_img)
		mlx_destroy_image(game->ptr_mlx, game->drawing_img.mlx_img);
	if (game->img.mlx_img)
		mlx_destroy_image(game->ptr_mlx, game->img.mlx_img);
	if (game->ptr_window)
		mlx_destroy_window(game->ptr_mlx, game->ptr_window);
	if (game->ptr_mlx)
	{
		mlx_destroy_display(game->ptr_mlx);
		free(game->ptr_mlx);
	}
	if (game->ray)
		free(game->ray);
	if (game)
		free(game);
}

void	game_refresh(t_pge *game)
{
	t_vi	x;
	t_pxl		pxl;

	x.x = 0;
	while (x.x < game->img.width)
	{
		x.y = 0;
		while (x.y < game->img.height)
		{
			get_pixel_from_img(game->drawing_img, x.x / game->pxlwidth,
				x.y / game->pxlheight, &pxl);
			draw_pixel(&x, game, &game->img, &pxl);
			x.y++;
		}
		x.x++;
	}
	mlx_put_image_to_window(game->ptr_mlx, game->ptr_window,
		game->img.mlx_img, 0, 0);
}
