/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:36:58 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/22 16:45:16 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

t_pxl	set_pxl_argb(unsigned char const red, unsigned char const green,
	unsigned char const blue, unsigned char const alpha)
{
	t_pxl	pxl;

	pxl.alpha = alpha;
	pxl.red = red;
	pxl.green = green;
	pxl.blue = blue;
	pxl.color = pxl.alpha * 16777216 + pxl.red * 65536 + pxl.green * 256
		+ pxl.blue;
	return (pxl);
}

void	set_pxl_hex(unsigned int const color, t_pxl *pxl)
{
	pxl->color = color;
	pxl->blue = (unsigned char)pxl->color % 256;
	pxl->color /= 256;
	pxl->green = (unsigned char)pxl->color % 256;
	pxl->color /= 256;
	pxl->red = (unsigned char)pxl->color % 256;
	pxl->color /= 256;
	pxl->alpha = (unsigned char)pxl->color % 256;
	pxl->color = color;
	return ;
}

short int	draw_pixel(t_vi *xy, t_pge *game, t_im *img, t_pxl *pxl)
{
	unsigned int	*pixel;

	(void)game;
	pixel = (unsigned int *)img->addr;
	if (xy->x >= img->width || xy->x < 0 || xy->y >= img->height
		|| xy->y < 0 || pxl->alpha == 255)
		return (1);
	pixel[xy->y * img->width + xy->x] = pxl->red * 65536 + pxl->green * 256
		+ pxl->blue;
	return (1);
}
