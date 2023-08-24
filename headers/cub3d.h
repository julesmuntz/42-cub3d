/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:20:59 by julmuntz          #+#    #+#             */
/*   Updated: 2023/08/24 16:32:19 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "PixelGameEngine.h"
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
# define RED "\033[0;31m"
# define NONE "\033[0;0m"

// /* Rendering Datastruct */
// typedef struct s_im
// {
// 	void		*mlx_img;
// 	char		*addr;
// 	int			bpp;
// 	int			line_len;
// 	int			endian;
// }				t_im;

// /* .xpm Image Datastruct */
// typedef struct s_xpm
// {
// 	void		*mlx_img;
// 	char		*addr;
// 	int			bpp;
// 	int			line_len;
// 	int			endian;
// 	int			width;
// 	int			height;
// }				t_xpm;

// /* .cub File Datastruct */
// typedef struct s_cub
// {
// 	char		*north_texture;
// 	char		*south_texture;
// 	char		*west_texture;
// 	char		*east_texture;
// 	int			*floor_color;
// 	int			*ceiling_color;

// 	bool		north_found;
// 	bool		south_found;
// 	bool		west_found;
// 	bool		east_found;
// 	bool		ceiling_found;
// 	bool		floor_found;
// 	bool		map_found;
// }				t_cub;

// /* MLX Datastruct */
// typedef struct s_mlx
// {
// 	void		*ptr_mlx;
// 	void		*ptr_window;
// 	t_im		img;
// 	t_xpm		wall;
// 	t_cub		cub;
// }				t_mlx;

/* Global Variables (To Be Removed) */
extern char		**g_map;
extern float	g_player_x;
extern float	g_player_y;
extern float	g_player_a;
extern int		g_screen_width;
extern int		g_screen_height;
extern float	g_fov;
extern float	g_map_depth;
extern bool		g_gofront;
extern bool		g_goback;
extern bool		g_goleft;
extern bool		g_goright;
extern bool		g_lookleft;
extern bool		g_lookright;
extern int		g_pixels;
extern char		*g_file_path;

// /* Movement Related Functions */
// void			go_front(float n);
// void			go_back(float n);
// void			go_left(float n);
// void			go_right(float n);
// int				ft_loop(t_mlx *mlx);
// int				ft_key_press(int keysym, t_mlx *mlx);
// int				ft_key_release(int keysym, t_mlx *mlx);

// /* Map Related Functions */
int				init_map(t_pge *game, char *arg);

// /* Textures Related Functions */
// int				init_textures(t_mlx *mlx, t_cub *cub, char *arg);
// int				set_texture_to_walls(char *tex_path, t_mlx *mlx, t_cub *cub);

// /* Colors Related Functions */
// int				xpm_color(t_mlx *mlx, float x, float y);
// int				init_colors(t_cub *cub, char *arg);
// int				rgb_to_hex(int *rgb);
// int				color_interpolation(float color1, float color2, float dist);
// int				color_interpolation_rgb(int color1, int color2, float dist);

// /* Rendering Related Functions */
// int				trace_into_image(t_mlx *mlx, char **map);

// /* Errors Handling Functions */
// int				check_file(t_cub *cub, char *arg);

/*player*/
void			set_fov(float const fov, t_player *player);
t_player		*set_player(t_vi const *pos, float const playera,
					float const fov);
t_xpm	*texture_choice(int const side, t_vi const *step, t_pge const *game);


#endif
