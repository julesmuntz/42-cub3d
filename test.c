# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>

# define PI 3.1415926535897932384626433832795028841971693993751058

/*structure d'image pour l'affichage de l'image dans la fenetre*/

typedef struct s_im
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_im;

/*structure mlx*/

typedef struct s_mlx
{
	void	*ptr_mlx;
	void	*ptr_window;
	t_im	img;
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
				"#...###....#",
				"#..........#",
				"#..........#",
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

int		ScreenWidth =  720;
int		ScreenHeigth = 560;

/*field of vue*/

float	FOV		= PI / 4;

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

/*fonction de deplacement avec un test et la demarche en fin de code
mais les deux lignes non commentees suffisent. point personnel a retravailler*/

void	go_front(float n)
{
	// if (abs(to_fx(PlayerA) % div_fx(PI, 2)) <= div_fx(PI, 2))
	// {
	// 	if (abs(to_fx(PlayerA) % div_fx(PI, 4)) <= div_fx(PI, 4))
	// 	{
	// 		float Y = sin(PlayerA) * n;
	// 		float X = cos(PlayerA) * n;
	// 		PlayerX += Y;
	// 		if (PlayerA >= 0)
	// 			PlayerY -= X;
	// 		else
	// 			PlayerY += X;
	// 	}
	// 	else
	// 	{
	// 		float X = sin(PlayerA) * n;
	// 		float Y = cos(PlayerA) * n;
	// 		PlayerX += Y;
	// 		if (PlayerA >= 0)
	// 			PlayerY -= X;
	// 		else
	// 			PlayerY += X;
	// 	}
	// }
	// else
	// {
	// 	if (abs((int)(PlayerA * (1 << 8)) % ((int)(PI * (1 << 8)) << 8 / (4 << 8))) <= ((int)(PI * (1 << 8)) << 8 / (4 << 8)))
	// 	{
	// 		float Y = sin(PlayerA) * n;
	// 		float X = cos(PlayerA) * n;
	// 		PlayerX -= Y;
	// 		if (PlayerA >= 0)
	// 			PlayerY -= X;
	// 		else
	// 			PlayerY += X;
	// 	}
	// 	else
	// 	{
	// 		float X = sin(PlayerA) * n;
	// 		float Y = cos(PlayerA) * n;
	// 		PlayerX -= Y;
	// 		if (PlayerA >= 0)
	// 			PlayerY -= X;
	// 		else
	// 			PlayerY += X;
	// 	}
	// }
	PlayerX += sinf(PlayerA) * n;
	PlayerY += cosf(PlayerA) * n;
}

/*same mais en arriere*/

void	go_back(float n)
{
	// PlayerA -= PI / 2;
	// if (abs(to_fx(PlayerA) % div_fx(PI, 2)) <= div_fx(PI, 2))
	// {
	// 	if (abs(to_fx(PlayerA) % div_fx(PI, 4)) <= div_fx(PI, 4))
	// 	{
	// 		float Y = sin(PlayerA) * n;
	// 		float X = cos(PlayerA) * n;
	// 		PlayerX -= X;
	// 		if (PlayerA >= 0)
	// 			PlayerY -= Y;
	// 		else
	// 			PlayerY += Y;
	// 	}
	// 	else
	// 	{
	// 		float X = sin(PlayerA) * n;
	// 		float Y = cos(PlayerA) * n;
	// 		PlayerX -= X;
	// 		if (PlayerA >= 0)
	// 			PlayerY -= Y;
	// 		else
	// 			PlayerY += Y;
	// 	}
	// }
	// else
	// {
	// 	if (abs((int)(PlayerA * (1 << 8)) % ((int)(PI * (1 << 8)) << 8 / (4 << 8))) <= ((int)(PI * (1 << 8)) << 8 / (4 << 8)))
	// 	{
	// 		float Y = sin(PlayerA) * n;
	// 		float X = cos(PlayerA) * n;
	// 		PlayerX += X;
	// 		if (PlayerA >= 0)
	// 			PlayerY -= Y;
	// 		else
	// 			PlayerY += Y;
	// 	}
	// 	else
	// 	{
	// 		float X = sin(PlayerA) * n;
	// 		float Y = cos(PlayerA) * n;
	// 		PlayerX += X;
	// 		if (PlayerA >= 0)
	// 			PlayerY -= Y;
	// 		else
	// 			PlayerY += Y;
	// 	}
	// }
	// PlayerA += PI / 2;
	PlayerX -= sinf(PlayerA) * n;
	PlayerY -= cosf(PlayerA) * n;
}

/*calcul pour chaque pixels d'un rayon pour savoir si on touche un mur ou si on est au dessus ou en dessous*/

 //rajouter un int i pour print un pixel sur deux (a retester. mes premiers tests ne rendaient pas)
int	trace_into_image(t_mlx *mlx, char **map)
{
	for (int x = 0; x < ScreenWidth; x++)
	{
		float rayangle = (PlayerA - FOV / 2) + ((float)x / (float)ScreenWidth) * FOV;
		float distanceToWall = 0.0f;
		int HitWall = 0; // bool = flase
		float eyeX = sinf(rayangle);
		float eyeY = cosf(rayangle);
		while (HitWall == 0)
		{
			distanceToWall += 0.1f;
			int testX = (int)(PlayerX + eyeX * distanceToWall);
			int testY = (int)(PlayerY + eyeY * distanceToWall);
			if (testX < 0 || testX >= 16 || testY < 0 || testY >= 16) //16 equivaut a la plus grande valeur de taille de la map
			{
				HitWall = 1;
				distanceToWall = 16;
			}
			else
			{
				if (map[testY][testX] == '#')
				{
					HitWall = 1;
				}
			}
		}
		int ceiling = (float)(ScreenHeigth / 2.0) - ScreenHeigth / ((float)distanceToWall);
		int floor = ScreenHeigth - ceiling;
		for (int y = 0; y < ScreenHeigth; y++)
		{
			if (y < ceiling)
				img_pix_put(&mlx->img, x, y, 3630315);
			else if (y <= floor)
				img_pix_put(&mlx->img, x, y, (int)(0xFF / (distanceToWall + 2.0f) * 2.f) << 8); /*print du mur avec un changement de couleur en fonstion de la distance. (a ameliorer)*/
			else
				img_pix_put(&mlx->img, x, y, 15435351);
		}
	}
	return (0);
}

/*fonction de loop*/

int	ft_loop(t_mlx *mlx)
{
	trace_into_image(mlx, map);

	mlx_put_image_to_window(mlx->ptr_mlx, mlx->ptr_window, mlx->img.mlx_img,
			0, 0);
	printf("Player Angle:	%f	Player X:	%f	Player Y:	%f\n", PlayerA, PlayerX, PlayerY);
	return (0);
}

/*gestion des entrees clavier (je ne geres pas encore la souris)*/

int	ft_key(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(mlx->ptr_mlx, mlx->img.mlx_img);
		mlx_destroy_window(mlx->ptr_mlx, mlx->ptr_window);
		mlx_destroy_display(mlx->ptr_mlx);
		free(mlx->ptr_mlx);
		exit(0);
	}
	else if (keysym == 'a')
		PlayerA -= 0.1f;
	else if (keysym == 'd')
		PlayerA += 0.1f;
	if (PlayerA >= PI)
		PlayerA = PI * -1;
	else if (PlayerA <= PI * -1)
		PlayerA = PI;
	else if (keysym == 'w')
		go_front(0.4f);
	else if (keysym == 's')
		go_back(0.3f);
	else
		ft_printf("Key: %d\n", keysym);
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


	trace_into_image(&mlx, map);

	mlx_put_image_to_window(mlx.ptr_mlx, mlx.ptr_window, mlx.img.mlx_img,
			0, 0);
	mlx_loop_hook(mlx.ptr_mlx, &ft_loop, &mlx);
	mlx_key_hook(mlx.ptr_window, &ft_key, &mlx);
	mlx_loop(mlx.ptr_mlx);
	mlx_destroy_display(mlx.ptr_mlx);
	free(mlx.ptr_mlx);
	return (0);
}


/* bouger en suivant pythagore*/
/*


playerA entre -PI /2 et PI / 2:
if (fabs(PlayerA % (PI / 4)) <= (PI / 4))

		  Y
		|---/
		|  /
X		| /0.1f
		|/
		A

sin(A) = Y / c ou Y = sin(A) * 0.1f
cos(A) = X / c ou X = cos(A) * 0.1f

PlayerX += X;
if (PlayerA >= 0)
	PlayerY += Y;
else
	PlayerY -= Y;



else



		    --/|
0.1f	 --/   | X
	A->	/------|
			Y


sin(A) = X / c ou X = sin(A) * 0.1f
cos(A) = Y / c ou Y = cos(A) * 0.1f


PlayerX += X;
if (PlayerA >= 0)
	PlayerY += Y;
else
	PlayerY -= Y;



else
if (fabs(PlayerA % (PI / 4)) <= (PI / 4))

		A
		|\
		| \0.1f
X		|  \
		|---\
		   Y

sin(A) = Y / c ou Y = sin(A) * 0.1f
cos(A) = X / c ou X = cos(A) * 0.1f

PlayerX -= X;
if (PlayerA >= 0)
	PlayerY += Y;
else
	PlayerY -= Y;

else



		    Y
	A->	\------|
		 --\   | X
	0.1f    --\|

sin(A) = X / c ou X = sin(A) * 0.1f
cos(A) = Y / c ou Y = cos(A) * 0.1f

PlayerX -= X;
if (PlayerA >= 0)
	PlayerY += Y;
else
	PlayerY -= Y;


*/


