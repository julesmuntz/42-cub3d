/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PixelGameEngine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:35:49 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/24 14:00:10 by gfranque         ###   ########.fr       */
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
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
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
}					t_cub;

typedef struct s_raycast
{
	float			cameraX;
	t_vf			rayDir;
	t_vi			map;
	t_vf			sideDist;
	t_vf			deltaDist;
	float			wallDist;
	t_vi			step;
	int				hit;
	int				side;
	int				wallSize;
	int				ceiling;
	int				floor;
	float			wallX;
	t_vi			xy;
}					t_raycast;

typedef struct s_player
{
	t_vf			pos;
	float			angle;
	t_vf			plan;
	t_vf			dir;
	float			fov;
}					t_player;

typedef struct s_pge
{
	void			*ptr_mlx;
	void			*ptr_window;
	t_im			img;
	t_im			drawing_img;
	short int		width;
	short int		height;
	short int		pxlwidth;
	short int		pxlheight;
	t_xpm			**xpm;
	int				key[127];
	t_cub			*cub;
	t_player		*player;
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
t_pge				*game_init(t_vi *screensize, t_vi *pxlsize,
						char const *name);
void				game_clear(t_pge *game);
void				game_refresh(t_pge *game);
short int			draw_pixel(t_vi *xy, t_pge *game, t_im *img, t_pxl *pxl);
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
void				print_sprite(t_xpm *xpm, t_vi coor, t_vi v, t_pge *game);
t_xpm				**new_xpm_array(t_xpm **xpm);
size_t				ft_xpmlen(t_xpm **xpm);
int					ft_key_press(int keysym, void *game);
int					ft_key_release(int keysym, void *game);
void				game_loop(t_pge *game);

#endif
