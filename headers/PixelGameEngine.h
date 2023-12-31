/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PixelGameEngine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:35:49 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/20 19:48:34 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXELGAMEENGINE_H
# define PIXELGAMEENGINE_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define R 0
# define G 1
# define B 2

typedef struct s_vi
{
	int				x;
	int				y;
}					t_vi;

typedef struct s_vf
{
	float			x;
	float			y;
}					t_vf;

typedef struct s_triangle
{
	t_vi			*x;
	t_vi			*y;
	t_vi			*z;
}					t_triangle;

typedef struct s_pxl
{
	unsigned char	alpha;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned int	color;
}					t_pxl;

typedef struct s_im
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_im;

typedef struct s_xpm
{
	void			*img;
	char			*addr;
	char			*name;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_xpm;

typedef struct s_cub
{
	char			*arg;

	char			*north_tex_path;
	char			*south_tex_path;
	char			*west_tex_path;
	char			*east_tex_path;
	int				*floor_color;
	int				*ceiling_color;
	char			**map;

	bool			north_found;
	bool			south_found;
	bool			west_found;
	bool			east_found;
	bool			ceiling_found;
	bool			floor_found;
	bool			map_found;
	bool			valid_map;
	bool			player_found;
	bool			multiple_players;
	bool			searching_for_map;
	bool			unreachable_areas;
	bool			wall_found;
	bool			door_found;
	bool			invalid_door;
	bool			invalid_map;

	int				map_width;
	int				map_height;
	float			map_depth;
	t_vi			player_pos;
	float			player_angle;

}					t_cub;

typedef struct s_portal
{
	bool			clicked_blue;
	bool			clicked_orange;
	bool			blue_led;
	bool			orange_led;
	bool			laserbeam;
	char			*crosshair_ent_path;
	char			*portalgun_ent_path;
	int				portal;

}					t_portal;

typedef struct s_raycast
{
	float			camerax;
	t_vf			raydir;
	t_vi			map;
	t_vf			sidedist;
	t_vf			deltadist;
	float			walldist;
	t_vi			step;
	int				hit;
	int				side;
	int				wallsize;
	int				ceiling;
	int				floor;
	float			wallx;
	t_vi			xy;
	t_vf			start;
	t_vf			end;
}					t_raycast;

typedef struct s_player
{
	t_vf			pos;
	t_vf			oldpos;
	float			angle;
	float			pitch;
	t_vf			plan;
	t_vf			dir;
	float			fov;
	t_vi			target;
	char			t;
	t_vi			portalb;
	t_vi			portalo;
	char			p;
	char			pb;
	char			po;
}					t_player;

typedef struct s_pge
{
	void			*ptr_mlx;
	void			*ptr_window;
	t_xpm			img;
	t_xpm			drawing_img;
	short int		width;
	short int		height;
	short int		pxlwidth;
	short int		pxlheight;
	t_xpm			**xpm;
	int				key[127];
	t_cub			*cub;
	t_player		*player;
	t_raycast		*ray;
	t_portal		*portal;
}					t_pge;

t_pxl				set_pxl_argb(unsigned char const red,
						unsigned char const green, unsigned char const blue,
						unsigned char const alpha);
void				set_pxl_hex(unsigned int const color, t_pxl *pxl);
void				get_pixel_from_img(t_im img, int x, int y, t_pxl *pxl);
void				get_pixel_from_xpm(t_xpm *xpm, int x, int y, t_pxl *pxl);
t_vi				set_vector(short int const x, short int const y);
t_vi				set_vector_by_points(t_vi const *a, t_vi const *b);
short int			compare_vector(t_vi const *a, t_vi const *b);
t_vi				copy_vector(t_vi const *a);
void				vector_rotation(t_vi *v, float angle);
t_vf				set_vectorf(float const x, float const y);
t_vf				set_vectorf_by_points(t_vf const *a, t_vf const *b);
short int			compare_vectorf(t_vf const *a, t_vf const *b);
t_vf				copy_vectorf(t_vf const *a);
void				vectorf_rotation(t_vf *v, float angle);
float				vector_dist(t_vi const *v);
float				vectorf_dist(t_vf const *v);
t_pge				*game_init(t_vi *screensize, t_vi *pxlsize);
void				game_clear(t_pge *game);
void				game_refresh(t_pge *game);
short int			draw_pixel(t_vi *xy, t_xpm *img, t_pxl *pxl);
void				draw_line(t_vi *xy, t_vi *v, t_pge *game, t_pxl *pxl);
void				draw_circle(t_vi *xy, short int const radius, t_pge *game,
						t_pxl *pxl);
void				fill_circle(t_vi *xy, short int const radius, t_pge *game,
						t_pxl *pxl);
void				draw_rectangle(t_vi *coor, t_vi *v, t_pge *game,
						t_pxl *pxl);
void				fill_rectangle(t_vi *coor, t_vi *v, t_pge *game,
						t_pxl *pxl);
short int			draw_triangle(t_triangle *t, t_pge *game, t_pxl *pxl);
void				fill_triangle(t_triangle *t, t_pge *game, t_pxl *pxl);
void				draw_string(t_vi *coor, char *str, t_pge *game, t_pxl *pxl);
int					new_xpm(char const *path, char const *name, t_xpm **xpm,
						t_pge *game);
t_xpm				**game_add_xpm(char const *path, char const *name,
						t_xpm **xpm, t_pge *game);
t_xpm				*add_xpm(char const *path, char const *name, t_pge *game);
void				free_xpm(t_xpm **xpm, t_pge *game);
short int			check_xpm(t_xpm **xpm);
void				print_sprite(t_xpm *xpm, t_vi coor, t_vi v, t_xpm *img);
t_xpm				**new_xpm_array(t_xpm **xpm);
t_xpm				*find_xpm(t_xpm **array, char *name);
size_t				ft_xpmlen(t_xpm **xpm);
int					ft_key_press(int keysym, void *game);
int					ft_key_release(int keysym, void *game);
void				game_loop(t_pge *game, int f(void *));
int					new_sprite(t_vi const *size, char const *name, t_xpm **xpm,
						t_pge *game);
t_xpm				**game_add_sprite(t_vi const *size, char const *name,
						t_xpm **xpm, t_pge *game);
void				cub_clear(t_pge *game);
t_pxl				pixel_interpolation(t_pxl const *color, t_pxl const *fog,
						float const dist, float const max);
short int			draw_pixel_xpm(t_vi *xy, t_xpm *xpm, t_pxl *pxl);
void				draw_line_xpm(t_vi *coor, t_vi *v, t_xpm *xpm, t_pxl *pxl);
void				draw_rectangle_xpm(t_vi *coor, t_vi *v, t_xpm *xpm,
						t_pxl *pxl);
void				fill_rectangle_xpm(t_vi const *coor, t_vi const *v,
						t_xpm *xpm, t_pxl *pxl);
void				draw_circle_xpm(t_vi *coor, int r, t_xpm *xpm, t_pxl *pxl);
void				fill_circle_xpm(t_vi *coor, int r, t_xpm *xpm, t_pxl *pxl);
int					ft_mouse_move(int x, int y, void *game);
int					game_open_window(t_pge *game, char const *name);

#endif
