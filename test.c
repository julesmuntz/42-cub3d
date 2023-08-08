# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>

# define PI 3.1415926535897932384626433832795028841971693993751058

/*
	Choses a faire:

	Faire le DDA

	Gerer les textures
*/

/*valeur de shift gauche 65505*/

/*structure d'image pour l'affichage de l'image dans la fenetre*/

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

/*structure mlx*/

typedef struct s_mlx
{
	void	*ptr_mlx;
	void	*ptr_window;
	t_im	img;
	t_xpm	wall;
}				t_mlx;

// char	*map[] = {"############",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#..........#",
// 				"#...###....#",
// 				"#..........#",
// 				"#..........#",
// 				"############",
// 				NULL};

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
				"#...########",
				"#..........#",
				"#...###....#",
				"############",
				NULL};

/*informations du joueur
position x
position y
angle de vue*/

float	PlayerX = 8.0f;
float	PlayerY = 8.0f;
float	PlayerA	= 0.0f;

/*taille de la fenetre*/

int		ScreenWidth =  1080;//720;
int		ScreenHeigth = 720;//560;

/*field of vue*/

float	FOV		= PI / 4;

/*taille "max" de la carte (definition a  revoir)*/

float MDepth		= 16.0f;

/*gestion des touches*/

int	gofront = 0;
int	goback	= 0;
int	goleft	= 0;
int	goright	= 0;

int	Pixls = 0;

void	img_pix_put(t_im *img, int x, int y, long color)
{
	int *const	pixel = (int *)img->addr;

	if (x >= ScreenWidth || x < 0 || y >= ScreenHeigth || y < 0)
		return ;
	pixel[y * ScreenWidth + x] = color;
}

/*fonctions de fixed point obsceletes mais utiles pour comprendre le go front en commentaire*/

int	to_fx(float n)
{
	return (n * (1 << 8));
}

int	mul_fx(float a, float b)
{
	int	c = a * (1 << 8);
	int d = b * (1 << 8);

	return (c * d >> 8);
}

int	div_fx(float a, float b)
{
	int	c = a * (1 << 8);
	int d = b * (1 << 8);

	if (d == 0)
		return (0);
	return ((c << 8) / d);
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


/*fonction de deplacement avec un test et la demarche en fin de code
mais les deux lignes non commentees suffisent. point personnel a retravailler*/

void	go_front(float n)
{
	PlayerX += sinf(PlayerA) * n;
	PlayerY += cosf(PlayerA) * n;
	if (map[(int)PlayerY][(int)PlayerX] == '#')
	{
		PlayerX -= sinf(PlayerA) * n;
		PlayerY -= cosf(PlayerA) * n;
	}
}

/*same mais en arriere*/

void	go_back(float n)
{
	PlayerX -= sinf(PlayerA) * n;
	PlayerY -= cosf(PlayerA) * n;
	if (map[(int)PlayerY][(int)PlayerX] == '#')
	{
		PlayerX += sinf(PlayerA) * n;
		PlayerY += cosf(PlayerA) * n;
	}
}

int	xpm_color(t_mlx *mlx, float x, float y)
{
	int const pixelx = mlx->wall.width * x;
	int const pixely = mlx->wall.height * y;
	int const *addresse = (int *)mlx->wall.addr;
	
	// printf("pixely = %d, pixelx = %d\n", (int)(mlx->wall.height * pixely), (int)(mlx->wall.height * pixelx));
	return (addresse[mlx->wall.width * pixely + pixelx]);
}

float	side_ray(float distanceToWall, float PlayerX, float PlayerY, float eyeX, float eyeY)
{
	int x;
	int	y;

	x = (int)(PlayerX + eyeX * (distanceToWall - 0.01f));
	y = (int)(PlayerY + eyeY * (distanceToWall - 0.01f));
	if (x != ((int)(PlayerX + eyeX * distanceToWall)))
	{
		if (x < ((int)(PlayerX + eyeX * distanceToWall)))
			return (1.0f - ((PlayerY + eyeY * distanceToWall) - (int)(PlayerY + eyeY * distanceToWall)));
		else
			return ((PlayerY + eyeY * distanceToWall) - (int)(PlayerY + eyeY * distanceToWall));
	}
	if (y < ((int)(PlayerY + eyeY * distanceToWall)))
		return ((PlayerX + eyeX * distanceToWall) - (int)(PlayerX + eyeX * distanceToWall));
	return (1.0f - ((PlayerX + eyeX * distanceToWall) - (int)(PlayerX + eyeX * distanceToWall)));
}

/*calcul pour chaque pixels d'un rayon pour savoir si on touche un mur ou si on est au dessus ou en dessous*/

 //rajouter un int i pour print un pixel sur deux (a retester. mes premiers tests ne rendaient pas)
int	trace_into_image(t_mlx *mlx, char **map)
{
	// for (int x = 0; x < ScreenWidth; x++)
	for (int x = Pixls; x < ScreenWidth; x += 2)
	{
		float rayangle = (PlayerA - FOV / 2) + ((float)x / (float)ScreenWidth) * FOV;
		float distanceToWall = 0.0f;
		int HitWall = 0; // bool = flase
		float eyeX = sinf(rayangle);
		float eyeY = cosf(rayangle);
		int testX;
		int testY;
		while (HitWall == 0)
		{
			distanceToWall += 0.01f;
			testX = (int)(PlayerX + eyeX * distanceToWall);
			testY = (int)(PlayerY + eyeY * distanceToWall);
			if (testX < 0 || testX >= MDepth || testY < 0 || testY >= MDepth) //16 equivaut a la plus grande valeur de taille de la map
			{
				HitWall = 1;
				distanceToWall = MDepth;
			}
			else
			{
				if (map[testY][testX] == '#')
				{
					HitWall = 1;
				}
			}
		}
		int	ceiling = (float)(ScreenHeigth / 2.0) - ScreenHeigth / ((float)distanceToWall);
		int floor = ScreenHeigth - ceiling;
		float	texturevalue;
		texturevalue = side_ray(distanceToWall, PlayerX, PlayerY, eyeX, eyeY);
		// for (int y = Pixls; y < ScreenHeigth; y += 2)
		for (int y = 0; y < ScreenHeigth; y ++)
		{
			if (y < ceiling)
			{
				float b = 1.0f - (y - ScreenHeigth / 2.0f) / (ScreenHeigth / 2.0f);
				img_pix_put(&mlx->img, x, y, color_interpolation_rgb(0x3764EB, 0x3EBDF5, (b / 3.0f) * MDepth));
			}
			else if (y <= floor)
				img_pix_put(&mlx->img, x, y, color_interpolation_rgb(xpm_color(mlx, texturevalue, (float)(y - ceiling) / (float)(floor - ceiling)), 0x000000, distanceToWall));
				// img_pix_put(&mlx->img, x, y, color_interpolation_rgb(0xAB7246, 0x000000, distanceToWall));
			else
			{
				float b = 1.0f - (y - ScreenHeigth / 2.0f) / (ScreenHeigth / 2.0f);
				img_pix_put(&mlx->img, x, y, color_interpolation_rgb(0xF59126, 0x000000, b * MDepth));
			}
		}
	}
	if (Pixls == 0)
		Pixls = 1;
	else
		Pixls = 0;
	return (0);
}

// int	dda_into_image(t_mlx mlx, char **map)
// {
// 	for (int x = 0; x < ScreenWidth; x++)
// 	{
// 		float rayangle = (PlayerA - FOV / 2) + ((float)x / (float)ScreenWidth) * FOV;
// 		float distanceToWall = 0.0f;
// 		int HitWall = 0; // bool = flase
		
// 	}
// }

/*fonction de loop*/

int	ft_loop(t_mlx *mlx)
{
	if (goleft == 1)
		PlayerA -= 0.015f;
	if (goright == 1)
		PlayerA += 0.015f;
	if (gofront == 1)
		go_front(0.08f);
	if (goback == 1)
		go_back(0.08f);

	trace_into_image(mlx, map);

	mlx_put_image_to_window(mlx->ptr_mlx, mlx->ptr_window, mlx->img.mlx_img,
			0, 0);
	printf("Player Angle:	%f	Player X:	%f	Player Y:	%f\n", PlayerA, PlayerX, PlayerY);
	return (0);
}

/*gestion des entrees clavier (je ne geres pas encore la souris)*/

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

int main()
{
	printf("%f %f %f\n", PlayerX, PlayerY, PlayerA);
	for (int i = 0; map[i]; i++)
		printf("%d:	%ld:	%s\n", i, ft_strlen(map[i]), map[i]);
	t_mlx	mlx;
	mlx.ptr_mlx = mlx_init();
	mlx.ptr_window = mlx_new_window(mlx.ptr_mlx, ScreenWidth, ScreenHeigth, "cub");
	mlx.img.mlx_img = mlx_new_image(mlx.ptr_mlx, ScreenWidth, ScreenHeigth);
	mlx.img.addr = mlx_get_data_addr(mlx.img.mlx_img, &mlx.img.bpp,
			&mlx.img.line_len, &mlx.img.endian);
	mlx.wall.mlx_img = mlx_xpm_file_to_image(mlx.ptr_mlx, "./Assets/Stitch.xpm", &mlx.wall.width, &mlx.wall.height);
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


	trace_into_image(&mlx, map);

	mlx_put_image_to_window(mlx.ptr_mlx, mlx.ptr_window, mlx.img.mlx_img,
			0, 0);
	mlx_loop_hook(mlx.ptr_mlx, &ft_loop, &mlx);
	// mlx_key_hook(mlx.ptr_window, &ft_key, &mlx);
	mlx_hook(mlx.ptr_window, KeyPress, KeyPressMask, &ft_key_press, &mlx);
	mlx_hook(mlx.ptr_window, KeyRelease, KeyReleaseMask, &ft_key_release, &mlx);
	mlx_loop(mlx.ptr_mlx);
	mlx_destroy_display(mlx.ptr_mlx);
	free(mlx.ptr_mlx);
	return (0);
}
