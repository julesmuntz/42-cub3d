/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:20:59 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/26 18:08:51 by gfranque         ###   ########.fr       */
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

# define PI 3.1415926535897932384626433832795028841971693993751058
# define R 0
# define G 1
# define B 2

/* Global Variables (To Be Removed) */
extern int		g_screen_width;
extern int		g_screen_height;
extern float	g_fov;
extern bool		g_gofront;
extern bool		g_goback;
extern bool		g_goleft;
extern bool		g_goright;
extern bool		g_lookleft;
extern bool		g_lookright;
extern int		g_pixels;

int				init_map(t_pge *game, char *arg);
int				init_colors(t_pge *game, char *arg);
int				init_textures(t_pge *game, char *arg);
int				check_file(t_pge *game, char *arg);
void			print_error(char *str);
t_cub			*init_cub(void);
bool			invalid_extension(char *filename);

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

#endif
