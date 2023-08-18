/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:43:12 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/19 12:56:50 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_loop(t_mlx *mlx)
{
	if (g_lookleft == 1)
		g_player_a -= 0.03f;
	if (g_lookright == 1)
		g_player_a += 0.03f;
	if (g_goleft == 1)
		go_left(0.08f);
	if (g_goright == 1)
		go_right(0.08f);
	if (g_gofront == 1)
		go_front(0.08f);
	if (g_goback == 1)
		go_back(0.08f);
	trace_into_image(mlx, g_map);
	mlx_put_image_to_window(mlx->ptr_mlx, mlx->ptr_window, mlx->img.mlx_img, 0,
			0);
	return (0);
}

int	ft_key_press(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(mlx->ptr_mlx, mlx->img.mlx_img);
		mlx_destroy_image(mlx->ptr_mlx, mlx->wall.mlx_img);
		mlx_destroy_window(mlx->ptr_mlx, mlx->ptr_window);
		mlx_destroy_display(mlx->ptr_mlx);
		free(mlx->ptr_mlx);
		exit(0);
	}
	else if (keysym == XK_Left)
		g_lookleft = true;
	else if (keysym == XK_Right)
		g_lookright = true;
	else if (keysym == 'w')
		g_gofront = true;
	else if (keysym == 'a')
		g_goleft = true;
	else if (keysym == 's')
		g_goback = true;
	else if (keysym == 'd')
		g_goright = true;
	return (0);
}

int	ft_key_release(int keysym, t_mlx *mlx)
{
	(void)mlx;
	(void)keysym;
	if (keysym == XK_Left)
		g_lookleft = false;
	else if (keysym == XK_Right)
		g_lookright = false;
	else if (keysym == 'w')
		g_gofront = false;
	else if (keysym == 'a')
		g_goleft = false;
	else if (keysym == 's')
		g_goback = false;
	else if (keysym == 'd')
		g_goright = false;
	return (0);
}
