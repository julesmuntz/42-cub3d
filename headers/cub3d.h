/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:20:59 by julmuntz          #+#    #+#             */
/*   Updated: 2023/09/22 11:50:39 by gfranque         ###   ########.fr       */
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

int			init_map(t_pge *game, char *arg);
int			init_colors(t_pge *game, char *arg);
int			init_textures(t_pge *game, char *arg);
int			check_file(t_pge *game, char *arg);
void		print_error(char *str);
t_cub		*init_cub(void);
bool		invalid_extension(char *filename);
int			check_map(t_pge *game, char *arg);
void		set_fov(float const fov, t_player *player);
t_player	*set_player(t_vi const *pos, float const playera, float const fov);
t_xpm		*texture_choice(t_raycast *ray, t_pge const *game);
int			add_texture(t_pge *game);
void		raycast_init(t_pge *game, t_vf start, t_xpm *img);
void		raycast_dda(t_pge *game, t_raycast *ray, t_vf *start, t_xpm *img);
void		raycast_dda_collision(t_pge *game, t_raycast *ray, t_xpm *img);
void		raycast_dda_setup(t_pge *game, t_raycast *ray, t_xpm *img);
void		raycast_dda_trace(t_pge *game, t_raycast *ray, t_xpm *texture,
				t_xpm *img);
void		check_movements(t_pge *game);
int			cub_launch(void *g);
void		look_direction(t_pge *game, float n);
void		fog_generation(t_pxl *pxl, float *dist, t_pge *game);
bool		check_collision(t_pge *game);
float		dist_interpolation(t_pge *game);
t_portal	*init_portal(void);
void		refresh_portal_colors(t_pge *game);
void		print_portal_gun(t_pge *game);
void		print_crosshair(t_pge *game);
void		print_laserbeam(t_pge *game);
int			add_portal_texture(t_pge *game);
void		portal_check(t_pge *game);
void		calculate_map_dimensions(t_pge *game, int fd);
void		flood_fill(t_pge *game, int a, int b, bool *failure);
void		set_pxl_for_dda(t_pge *game, t_xpm *texture, float *dist,
				t_pxl *pxl);
int			door_is_close(t_pge *game, int x, int y);
void		check_door(t_pge *game, int *a, int *b);
int			ft_is_in_charcount(char *str, char tofind);
void		check_portal(t_pge *game);
void		raycast_portal(t_pge *game, t_raycast *ray, float walldist,
				char dir);
t_vf		same_side(t_pge *game, t_raycast *ray, char dir);
t_vf		opposite_side(t_pge *game, t_raycast *ray, char dir);
t_vf		right_side(t_pge *game, t_raycast *ray, char dir);
t_vf		left_side(t_pge *game, t_raycast *ray, char dir);
int			portal_side_check(t_pge *game, t_raycast *ray, char p);
int			is_a_portal(t_pge *game, t_raycast *ray);
t_vf		set_portal_value(t_pge *game, t_raycast *ray, char dir);
int			check_collision_ray(t_pge *game, t_raycast *ray);
int			check_side(t_pge *game, t_raycast *ray, char p);
char		get_side(t_raycast	*ray);
void		update_portal_value(t_raycast *ray, t_vf *start, char side);
void		update_portal_ray(t_raycast *ray, char in, char out);
char		check_pos_side(t_pge *game);
void		teleport_rotation(t_pge *game, char dir, char from);
char		collition_in_portal(t_pge *game);
void		check_portal_2(t_pge *game);
void		portal_orientation(t_pge *game, char *portal);
int			is_in_the_right_place(t_pge *game, t_vi *portal, char side);
int			ft_read(char *str);

#endif
