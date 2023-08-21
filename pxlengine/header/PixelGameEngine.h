/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PixelGameEngine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:35:49 by gfranque          #+#    #+#             */
/*   Updated: 2023/08/21 17:46:32 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIXELGAMEENGINE_H
# define PIXELGAMEENGINE_H

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vector
{
	short int	x;
	short int	y;
}				t_vector;

typedef struct s_triangle
{
	t_vector	*x;
	t_vector	*y;
	t_vector	*z;
}				t_triangle;

typedef struct s_pxl
{
	unsigned char		alpha;
	unsigned char		red;
	unsigned char		green;
	unsigned char		blue;
	unsigned int		color;
}						t_pxl;

typedef struct s_im
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_im;

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

typedef struct s_pge
{
	void		*ptr_mlx;
	void		*ptr_window;
	t_im		img;
	t_im		drawing_img;
	short int	width;
	short int	height;
	short int	pxlwidth;
	short int	pxlheight;
	t_xpm		**xpm;
	int			key[127];

}			t_pge;

t_pxl			set_pxl_argb(unsigned char const red, unsigned char const green,
					unsigned char const blue, unsigned char const alpha);
void			set_pxl_hex(unsigned int const color, t_pxl *pxl);
void			get_pixel_from_img(t_im img, int x, int y, t_pxl *pxl);
void			get_pixel_from_xpm(t_xpm *xpm, int x, int y, t_pxl *pxl);
t_vector		set_vector(short int const x, short int const y);
t_vector		set_vector_by_points(t_vector const *a, t_vector const *b);
short int		compare_vector(t_vector const *a, t_vector const *b);
t_vector		copy_vector(t_vector const *a);
t_pge			*game_init(t_vector *screensize, t_vector *pxlsize, char const *name);
void			game_clear(t_pge *game);
void			game_refresh(t_pge *game);
short int		draw_pixel(t_vector *xy, t_pge *game, t_im *img, t_pxl *pxl);
void			draw_line(t_vector *xy, t_vector *v,
					t_pge *game, t_pxl *pxl);
void			draw_circle(t_vector *xy, short int const radius,
					t_pge *game, t_pxl *pxl);
void			fill_circle(t_vector *xy, short int const radius,
					t_pge *game, t_pxl *pxl);
void			draw_rectangle(t_vector *coor, t_vector *v, t_pge *game,
					t_pxl *pxl);
void			fill_rectangle(t_vector *coor, t_vector *v, t_pge *game,
					t_pxl *pxl);
short int		draw_triangle(t_triangle *t, t_pge *game, t_pxl *pxl);
void			fill_triangle(t_triangle *t, t_pge *game, t_pxl *pxl);
void			draw_string(t_vector *coor, char *str, t_pge *game,
					t_pxl *pxl);
int				new_xpm(char const *path, char const *name,t_xpm **xpm, t_pge *game);
t_xpm	 		**game_add_xpm(char const *path, char const *name, t_xpm **xpm, t_pge *game);
t_xpm			*add_xpm(char const *path, char const *name, t_pge *game);
void			free_xpm(t_xpm **xpm, t_pge *game);
short int 		check_xpm(t_xpm **xpm);
void			print_sprite(t_xpm *xpm, t_vector coor, t_vector v, t_pge *game);
t_xpm			**new_xpm_array(t_xpm **xpm);
size_t			ft_xpmlen(t_xpm **xpm);
int				ft_key_press(int keysym, void *game);
int				ft_key_release(int keysym, void *game);
void			game_loop(t_pge *game);

#endif
