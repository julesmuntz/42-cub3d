#ifndef CUB3D_H
# define CUB3D_H

# include "./../libft/libft.h"
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

typedef struct s_im
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_im;

typedef struct s_xpm
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_xpm;

extern char		**map;
extern float	PlayerX;
extern float	PlayerY;
extern float	PlayerA;
extern int		ScreenWidth;
extern int		ScreenHeight;
extern float	FOV;
extern float	MDepth;
extern bool		gofront;
extern bool		goback;
extern bool		goleft;
extern bool		goright;
extern bool		lookleft;
extern bool		lookright;
extern int		Pixls;
extern char		*file_path;

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			*floor_color;
	int			*ceiling_color;
}				t_config;

typedef struct s_mlx
{
	void		*ptr_mlx;
	void		*ptr_window;
	t_im		img;
	t_xpm		wall;
}				t_mlx;

/*fonctions*/

int				init_map(char *arg);

#endif
