# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>

# define PI 3.1415926535897932384626433832795028841971693993751058

typedef struct s_im
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_im;

typedef struct s_xpm
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}				t_xpm;

typedef struct s_mlx
{
	void	*ptr_mlx;
	void	*ptr_window;
	t_im	img;
	t_xpm	wall;
}				t_mlx;

char	*map[] = {"############",
				"#..........#",
				"#..........#",
				"#..........#",
				"#..........#",
				"#..........#",
				"#..........#",
				"#..........#",
				"#..........#",
				"#..........#",
				"#..........#",
				"#..........#",
				"#...######.#",
				"#..........#",
				"#...###....#",
				"############",
				NULL};

float	PlayerX = 8.0f;
float	PlayerY	= 8.0f;
float	PlayerA	= -M_PI_2;

float	PlanX = 0.0f;
float	PlanY = 0.40f;
float	dirX = -1.0f;
float	dirY = 0.0f;

int		ScreenWidth = 1080;
int		ScreenHeight = 720;

int MDepth = 20;

int	gofront = 0;
int	goback	= 0;
int	goleft	= 0;
int	goright	= 0;

float	vecteur_dist(float x, float y)
{
	return (sqrtf((x * x) + (y * y)));
}

void	set_FOV(float Fov)
{
	PlanY = vecteur_dist(dirX, dirY) * tanf(Fov / 2);
}

void	vector_rotation(float *x, float *y, float angle)
{
	float xp;
	float yp;

	xp = *x * cosf(angle) - *y * sinf(angle);
	yp = *x * sin(angle) + *y * cosf(angle);
	*x = xp;
	*y = yp;
}

void	img_pix_put(t_im *img, int x, int y, long color)
{
	int *const	pixel = (int *)img->addr;

	if (x >= ScreenWidth || x < 0 || y >= ScreenHeight || y < 0)
		return ;
	pixel[y * ScreenWidth + x] = color;
}

int	color_interpolation(float color1, float color2, float dist)
{
	int	color3;

	if (dist >= MDepth)
		return (color2);
	color3 = (int)(color1 * ((MDepth - dist) / (MDepth - 0.1f)) + color2 * ((dist - 0.1f) / (MDepth - 0.1f)));
	return (color3);
}

int color_interpolation_rgb(int color1, int color2, float dist)
{
    int colorrgb1[3];
    int colorrgb2[3];
    int colorrgb3[3];
    
    colorrgb1[2] = color1 % 256;
    color1 = color1 / 256;
    colorrgb1[1] = color1 % 256;
    color1 = color1 / 256;
    colorrgb1[0] = color1 % 256;
    colorrgb2[2] = color2 % 256;
    color1 = color1 / 256;
    colorrgb2[1] = color2 % 256;
    color1 = color1 / 256;
    colorrgb2[0] = color2 % 256;
    colorrgb3[0] = color_interpolation(colorrgb1[0], colorrgb2[0], dist);
    colorrgb3[1] = color_interpolation(colorrgb1[1], colorrgb2[1], dist);
    colorrgb3[2] = color_interpolation(colorrgb1[2], colorrgb2[2], dist);
    return (colorrgb3[0] * 65536 + colorrgb3[1] * 256 + colorrgb3[2]);
}

int	xpm_color(t_mlx *mlx, float x, float y)
{
	int const pixelx = mlx->wall.width * x;
	int const pixely = mlx->wall.height * y;
	int const *addresse = (int *)mlx->wall.addr;
	
	return (addresse[mlx->wall.width * pixely + pixelx]);
}

int	digital_differential_analysis(t_mlx *mlx)
{
	for (int x = 0; x < ScreenWidth; x++)
	{
		float cameraX = (float)x / (float)ScreenWidth * 2.f - 1.f;
		float rayDirX = dirX + PlanX * cameraX;
		float rayDirY = dirY + PlanY * cameraX;
		int mapX = (int)PlayerX;
		int mapY = (int)PlayerY;
		float sideDistX;
		float sideDistY;
		float deltaDistX = fabsf(1.f / rayDirX);
		float deltaDistY = fabsf(1.f / rayDirY);
		float wallDist;
		int	stepX;
		int stepY;
		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (PlayerX - (float)mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = ((float)mapX + 1.0f - PlayerX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (PlayerY - (float)mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = ((float)mapY + 1.0f - PlayerY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (map[mapY][mapX] == '#')
				hit = 1;
		}
		if (side == 0)
			wallDist = (sideDistX - deltaDistX);
		else
			wallDist = (sideDistY - deltaDistY);
		int	wall_size = (float)ScreenHeight / wallDist * (ScreenHeight / (float)ScreenWidth);
		int	ceiling = (float)(ScreenHeight) / 2.f - wall_size / 2.f;
		int floor = ceiling + wall_size;
		float wallX;
		if (side == 0)
			wallX = PlayerY + wallDist * rayDirY;
		else
			wallX = PlayerX + wallDist * rayDirX;
		wallX -= (int)(wallX);
		wallX = 1.0f - wallX;
		if ((side == 0 && rayDirX < 0) || (side == 1 && rayDirY > 0))
			wallX = 1.0f - wallX;
		for (int y = 0; y < ScreenHeight; y++)
		{
			if (y < ceiling)
			{
				float b = 1.0f - (y - ScreenHeight / 2.0f) / (ScreenHeight / 2.0f);
				img_pix_put(&mlx->img, x, y, color_interpolation_rgb(0x3764EB, 0x3EBDF5, (b / 3.0f) * MDepth));
			}
			else if (y < floor)
			{
				img_pix_put(&mlx->img, x, y, color_interpolation_rgb(xpm_color(mlx, wallX, (float)(y - ceiling) / (float)(floor - ceiling)), 0x000000, wallDist));
			}
			else
			{
				float b = 1.0f - (y - ScreenHeight / 2.0f) / (ScreenHeight / 2.0f);
				img_pix_put(&mlx->img, x, y, color_interpolation_rgb(0xF59126, 0x000000, b * MDepth));
			}
		}
	}
	return (0);
}


void	go_front(float n)
{
	PlayerX += sinf(PlayerA) * n;
	PlayerY += cosf(PlayerA) * n;
	if (map[(int)(PlayerY + 0.1f)][(int)(PlayerX)] == '#')
	{
		PlayerX -= sinf(PlayerA) * n;
		PlayerY -= cosf(PlayerA) * n;
	}
	else if (map[(int)(PlayerY - 0.1f)][(int)(PlayerX)] == '#')
	{
		PlayerX -= sinf(PlayerA) * n;
		PlayerY -= cosf(PlayerA) * n;
	}
	else if (map[(int)(PlayerY)][(int)(PlayerX + 0.1f)] == '#')
	{
		PlayerX -= sinf(PlayerA) * n;
		PlayerY -= cosf(PlayerA) * n;
	}
	else if (map[(int)(PlayerY)][(int)(PlayerX - 0.1f)] == '#')
	{
		PlayerX -= sinf(PlayerA) * n;
		PlayerY -= cosf(PlayerA) * n;
	}
}

void	go_back(float n)
{
	PlayerX -= sinf(PlayerA) * n;
	PlayerY -= cosf(PlayerA) * n;
	if (map[(int)(PlayerY + 0.1f)][(int)(PlayerX)] == '#')
	{
		PlayerX += sinf(PlayerA) * n;
		PlayerY += cosf(PlayerA) * n;
	}
	else if (map[(int)(PlayerY - 0.1f)][(int)(PlayerX)] == '#')
	{
		PlayerX += sinf(PlayerA) * n;
		PlayerY += cosf(PlayerA) * n;
	}
	else if (map[(int)(PlayerY)][(int)(PlayerX + 0.1f)] == '#')
	{
		PlayerX += sinf(PlayerA) * n;
		PlayerY += cosf(PlayerA) * n;
	}
	else if (map[(int)(PlayerY)][(int)(PlayerX - 0.1f)] == '#')
	{
		PlayerX += sinf(PlayerA) * n;
		PlayerY += cosf(PlayerA) * n;
	}
}

int	ft_key_press(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(mlx->ptr_mlx, mlx->img.mlx_img);
		mlx_destroy_image(mlx->ptr_mlx, mlx->wall.mlx_img);
		mlx_destroy_window(mlx->ptr_mlx, mlx->ptr_window);
		mlx_destroy_display(mlx->ptr_mlx);
		free(mlx->ptr_mlx);
		exit(0);
	}
	else if (keysym == 'a' || keysym == 65361)
		goleft = 1;
	else if (keysym == 'd' || keysym == 65363)
		goright = 1;
	else if (keysym == 'w' || keysym == 65362)
		gofront = 1;
	else if (keysym == 's' || keysym == 65364)
		goback = 1;
	else
		ft_printf("Key: %d\n", keysym);
	// (void)mlx;
	// ft_printf("Key press:	%d\n", keysym);
	return (0);
}

int	ft_key_release(int keysym, t_mlx *mlx)
{
	(void)mlx;
	(void)keysym;
	// ft_printf("Key release:	%d\n", keysym);
	if (keysym == 'a' || keysym == 65361)
		goleft = 0;
	else if (keysym == 'd' || keysym == 65363)
		goright = 0;
	else if (keysym == 'w' || keysym == 65362)
		gofront = 0;
	else if (keysym == 's' || keysym == 65364)
		goback = 0;
	return (0);
}

int	ft_loop(t_mlx *mlx)
{
	if (goleft == 1)
	{
		PlayerA -= 0.02f;
		vector_rotation(&dirX, &dirY, 0.02f);
		vector_rotation(&PlanX, &PlanY, 0.02f);
	}
	if (goright == 1)
	{
		PlayerA += 0.02f;
		vector_rotation(&dirX, &dirY, -0.02f);
		vector_rotation(&PlanX, &PlanY, -0.02f);
	}
	if (gofront == 1)
		go_front(0.08f);
	if (goback == 1)
		go_back(0.08f);

	digital_differential_analysis(mlx);

	mlx_put_image_to_window(mlx->ptr_mlx, mlx->ptr_window, mlx->img.mlx_img,
			0, 0);
	// printf("Player Angle:	%f	Player X:	%f	Player Y:	%f\n", PlayerA, PlayerX, PlayerY);
	return (0);
}

int	main(void)
{
	set_FOV(M_PI / 2.f);
	t_mlx	mlx;
	mlx.ptr_mlx = mlx_init();
	mlx.ptr_window = mlx_new_window(mlx.ptr_mlx, ScreenWidth, ScreenHeight, "cub");
	mlx.img.mlx_img = mlx_new_image(mlx.ptr_mlx, ScreenWidth, ScreenHeight);
	mlx.img.addr = mlx_get_data_addr(mlx.img.mlx_img, &mlx.img.bpp,
			&mlx.img.line_len, &mlx.img.endian);
	mlx.wall.mlx_img = mlx_xpm_file_to_image(mlx.ptr_mlx, "./Assets/rockwall.xpm", &mlx.wall.width, &mlx.wall.height);
	if (mlx.wall.mlx_img == NULL)
	{
			mlx_destroy_image(mlx.ptr_mlx, mlx.img.mlx_img);
			mlx_destroy_window(mlx.ptr_mlx, mlx.ptr_window);
			mlx_destroy_display(mlx.ptr_mlx);
			free(mlx.ptr_mlx);
			exit(0);
	}
	mlx.wall.addr = mlx_get_data_addr(mlx.wall.mlx_img, &mlx.wall.bpp,
			&mlx.wall.line_len, &mlx.wall.endian);
	digital_differential_analysis(&mlx);
	mlx_put_image_to_window(mlx.ptr_mlx, mlx.ptr_window, mlx.img.mlx_img,
			0, 0);
	mlx_loop_hook(mlx.ptr_mlx, &ft_loop, &mlx);
	mlx_hook(mlx.ptr_window, KeyPress, KeyPressMask, &ft_key_press, &mlx);
	mlx_hook(mlx.ptr_window, KeyRelease, KeyReleaseMask, &ft_key_release, &mlx);
	mlx_loop(mlx.ptr_mlx);
	mlx_destroy_display(mlx.ptr_mlx);
	free(mlx.ptr_mlx);
	return (0);
}
