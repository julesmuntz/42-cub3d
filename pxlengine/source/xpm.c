/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:32 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/21 17:13:07 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PixelGameEngine.h"

int	new_xpm(char const *path, char const *name, t_xpm **xpm, t_pge *game)
{
	int	len;

	if (!path || !name)
		return (0);
	len = ft_xpmlen(xpm);
	xpm[len] = malloc(sizeof(t_xpm) * 1);
	if (!xpm[len])
		return (0);
	xpm[len]->img = mlx_xpm_file_to_image(game->ptr_mlx, (char *)path,
			&xpm[len]->width, &xpm[len]->height);
	if (!xpm[len]->img)
		return (0);
	xpm[len]->addr = mlx_get_data_addr(xpm[len]->img, &xpm[len]->bpp,
			&xpm[len]->line_len, &xpm[len]->endian);
	xpm[len]->name = (char *)name;
	return (1);
}

t_xpm	**game_add_xpm(char const *path, char const *name, t_xpm **xpm,
	t_pge *game)
{
	xpm = new_xpm_array(xpm);
	if (xpm == NULL)
		return (NULL);
	if (new_xpm(path, name, xpm, game) == 0)
		return (free_xpm(xpm, game), NULL);
	if (check_xpm(xpm) == 0)
		return (free_xpm(xpm, game), NULL);
	return (xpm);
}

void	free_xpm(t_xpm **xpm, t_pge *game)
{
	int	i;

	i = 0;
	if (!xpm)
		return ;
	while (xpm[i])
	{
		mlx_destroy_image(game->ptr_mlx, xpm[i]->img);
		free(xpm[i]);
		i++;
	}
	free(xpm);
	return ;
}

short int	check_xpm(t_xpm **xpm)
{
	int	i;
	int	j;

	i = 0;
	while (xpm[i])
	{
		j = 0;
		while (xpm[j])
		{
			if (i != j
				&& ft_strlen(xpm[i]->name) == ft_strlen(xpm[j]->name)
				&& ft_strncmp(xpm[i]->name, xpm[j]->name,
					ft_strlen(xpm[i]->name)) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
