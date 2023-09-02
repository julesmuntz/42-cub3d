/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:20:59 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/02 18:48:47 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "PixelGameEngine.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>

int				init_map(t_pge *game, char *arg);
int				init_colors(t_pge *game, char *arg);
int				init_textures(t_pge *game, char *arg);
int				check_file(t_pge *game, char *arg);
void			print_error(char *str);
t_cub			*init_cub(void);
bool			invalid_extension(char *filename);
int				check_map(t_pge *game, char *arg);
void			set_fov(float const fov, t_player *player);
t_player		*set_player(t_vi const *pos, float const playera,
					float const fov);
t_xpm			*texture_choice(int const side, t_vi const *step,
					t_pge const *game);
int				add_texture(t_pge *game);
void			raycast_init(t_pge *game);
void			raycast_dda(t_pge *game, t_raycast *ray);
void			raycast_dda_collision(t_pge *game, t_raycast *ray);
void			raycast_dda_setup(t_pge *game, t_raycast *ray);
void			raycast_dda_trace(t_pge *game, t_raycast *ray, t_xpm *texture);
void			check_movements(t_pge *game);
int				cub_launch(void *g);
void			look_direction(t_pge *game, float n);
void			fog_generation(t_pxl *pxl, float *dist, t_pge *game);
bool			check_collision(t_pge *game);
float			dist_interpolation(t_pge *game);
t_portal		*init_portal(void);
void			refresh_portal_colors(t_pge *game);

#endif
