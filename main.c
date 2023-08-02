#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include <X11/keysym.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define PI 3.1415926535897932384626433832795028841971693993751058
#define KEY_COUNT 65536
#define FPS 60
#define FRAME_TIME_US 1000000 / FPS

typedef struct s_im
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_im;

typedef struct s_mlx
{
	void	*ptr_mlx;
	void	*ptr_window;
	t_im	img;
}			t_mlx;

char		*map[] = {
	"############",
	"#..........#",
	"#..........#",
	"#..........#",
	"#..........#",
	"#..........#",
	"#..........#",
	"#..........#",
	"#......#...#",
	"#......#...#",
	"#....###...#",
	"#....#.....#",
	"#....#.....#",
	"#..........#",
	"#..........#",
	"############",
	NULL};

float		PlayerX = 3.0f;
float		PlayerY = 3.0f;
float		PlayerA = 0.0f;
float		PlayerPitch = 0.0f;

int			ScreenWidth = 720;
int			ScreenHeight = 560;

float		FOV = PI / 2;

bool		keys[KEY_COUNT];

void	img_pix_put(t_im *img, int x, int y, long color)
{
	int *const pixel = (int *)img->addr;
	if (x >= ScreenWidth || x < 0 || y >= ScreenHeight || y < 0)
		return ;
	pixel[y * ScreenWidth + x] = color;
}

int	to_fx(float n)
{
	return (n * (1 << 8));
}

int	mul_fx(float a, float b)
{
	int	c;
	int	d;

	c = a * (1 << 8);
	d = b * (1 << 8);
	return (c * d >> 8);
}

int	div_fx(float a, float b)
{
	int	c;
	int	d;

	c = a * (1 << 8);
	d = b * (1 << 8);
	if (d == 0)
		return (0);
	return ((c << 8) / d);
}

void	go_front(float n)
{
	PlayerX += sinf(PlayerA) * n;
	PlayerY += cosf(PlayerA) * n;
}

void	go_back(float n)
{
	PlayerX -= sinf(PlayerA) * n;
	PlayerY -= cosf(PlayerA) * n;
}

void	go_left(float n)
{
	PlayerX -= cosf(PlayerA) * n;
	PlayerY += sinf(PlayerA) * n;
}

void	go_right(float n)
{
	PlayerX += cosf(PlayerA) * n;
	PlayerY -= sinf(PlayerA) * n;
}

void	draw_wall_pixel(t_mlx *mlx, int x, int y, int initial_color,
		float distanceToWall)
{
	int	r;
	int	g;
	int	b;
	int	adjusted_color;

	r = (initial_color & 0xff0000) >> 16;
	g = (initial_color & 0x00ff00) >> 8;
	b = (initial_color & 0x0000ff);
	r = (int)(r / (distanceToWall + 2.0f) * 2.f);
	g = (int)(g / (distanceToWall + 2.0f) * 2.f);
	b = (int)(b / (distanceToWall + 2.0f) * 2.f);
	adjusted_color = (r << 16) + (g << 8) + b;
	img_pix_put(&mlx->img, x, y, adjusted_color);
}

void	cast_rays(t_mlx *mlx)
{
	float	rayangle;
	float	distanceToWall;
	float	eyeX;
	float	eyeY;
	int		testX;
	int		testY;
	int		ceiling;
	int		floor;
	int		HitWall;
	int		pitch_adjusted_ceiling;
	int		pitch_adjusted_floor;

	for (int x = 0; x < ScreenWidth; x++)
	{
		rayangle = (PlayerA - FOV / 2) + ((float)x / (float)ScreenWidth) * FOV;
		distanceToWall = 0.0f;
		HitWall = false;
		eyeX = sinf(rayangle);
		eyeY = cosf(rayangle);
		while (!HitWall)
		{
			distanceToWall += 0.1f;
			testX = (int)(PlayerX + eyeX * distanceToWall);
			testY = (int)(PlayerY + eyeY * distanceToWall);
			if (testX < 0 || testX >= 16 || testY < 0 || testY >= 16)
			{
				HitWall = true;
				distanceToWall = 16;
			}
			else if (map[testY][testX] == '#')
				HitWall = true;
		}
		ceiling = (float)(ScreenHeight / 2.0) - ScreenHeight
			/ ((float)distanceToWall);
		floor = ScreenHeight - ceiling;
		pitch_adjusted_ceiling = ceiling + PlayerPitch * 100;
		pitch_adjusted_floor = floor + PlayerPitch * 100;
		for (int y = 0; y < ScreenHeight; y++)
		{
			if (y < pitch_adjusted_ceiling)
				img_pix_put(&mlx->img, x, y, 0xadd8e6);
			else if (y <= pitch_adjusted_floor)
				draw_wall_pixel(mlx, x, y, 0xffe900, distanceToWall);
			else
				img_pix_put(&mlx->img, x, y, 0xffe900);
		}
	}
}

int	ft_key_press(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(mlx->ptr_mlx, mlx->img.mlx_img);
		mlx_destroy_window(mlx->ptr_mlx, mlx->ptr_window);
		mlx_destroy_display(mlx->ptr_mlx);
		free(mlx->ptr_mlx);
		exit(0);
	}
	else if (keysym >= 0 && keysym < KEY_COUNT)
		keys[keysym] = true;
	return (0);
}

int	ft_key_release(int keysym)
{
	if (keysym >= 0 && keysym < KEY_COUNT)
		keys[keysym] = false;
	return (0);
}

int	ft_mouse_move(int x, int y, t_mlx *mlx)
{
	int		last_x;
	int		last_y;
	float	delta_x;
	float	delta_y;

	last_x = ScreenWidth / 2;
	last_y = ScreenHeight / 2;
	delta_x = x - last_x;
	delta_y = y - last_y;
	PlayerA += delta_x * 0.0025f;
	PlayerPitch = fmax(fmin(PlayerPitch - delta_y * 0.005f, 10.0f), -10.0);
	last_x = x;
	last_y = y;
	mlx_mouse_move(mlx->ptr_mlx, mlx->ptr_window, ScreenWidth / 2, ScreenHeight
			/ 2);
	return (0);
}

void	update_camera_position(void)
{
	if (keys[XK_Left])
		PlayerA -= 0.05f;
	if (keys[XK_Right])
		PlayerA += 0.05f;
	if (keys[XK_Up])
		PlayerPitch = fmin(PlayerPitch + 0.1f, 10.0f);
	if (keys[XK_Down])
		PlayerPitch = fmax(PlayerPitch - 0.1f, -10.0f);
	if (keys[XK_w])
		go_front(0.1f);
	if (keys[XK_a])
		go_left(0.1f);
	if (keys[XK_s])
		go_back(0.1f);
	if (keys[XK_d])
		go_right(0.1f);
	if (PlayerA >= PI)
		PlayerA = PI * -1;
	else if (PlayerA <= PI * -1)
		PlayerA = PI;
}

int	ft_loop(t_mlx *mlx)
{
	struct timeval	start_time;
	struct timeval	end_time;
	long			elapsed_time_us;

	gettimeofday(&start_time, NULL);
	update_camera_position();
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->ptr_mlx, mlx->ptr_window, mlx->img.mlx_img, 0,
			0);
	printf("Player Angle:	%f	Player X:	%f	Player Y:	%f\n", PlayerA,
								PlayerX, PlayerY);
	gettimeofday(&end_time, NULL);
	elapsed_time_us = (end_time.tv_sec - start_time.tv_sec) * 1000000L
		+ (end_time.tv_usec - start_time.tv_usec);
	if (elapsed_time_us < FRAME_TIME_US)
		usleep(FRAME_TIME_US - elapsed_time_us);
	return (0);
}

int	main(void)
{
	t_mlx	mlx;

	printf("%f %f %f\n", PlayerX, PlayerY, PlayerA);
	for (int i = 0; map[i]; i++)
		printf("%d:	%ld:	%s\n", i, ft_strlen(map[i]), map[i]);
	mlx.ptr_mlx = mlx_init();
	mlx.ptr_window = mlx_new_window(mlx.ptr_mlx, ScreenWidth, ScreenHeight,
			"cub");
	mlx.img.mlx_img = mlx_new_image(mlx.ptr_mlx, ScreenWidth, ScreenHeight);
	mlx.img.addr = mlx_get_data_addr(mlx.img.mlx_img, &mlx.img.bpp,
			&mlx.img.line_len, &mlx.img.endian);
	cast_rays(&mlx);
	mlx_put_image_to_window(mlx.ptr_mlx, mlx.ptr_window, mlx.img.mlx_img, 0, 0);
	mlx_loop_hook(mlx.ptr_mlx, &ft_loop, &mlx);
	mlx_hook(mlx.ptr_window, 2, (1L << 0), ft_key_press, &mlx);
	mlx_hook(mlx.ptr_window, 3, (1L << 1), ft_key_release, &mlx);
	mlx_hook(mlx.ptr_window, 6, (1L << 6), ft_mouse_move, &mlx);
	mlx_loop(mlx.ptr_mlx);
	mlx_destroy_image(mlx.ptr_mlx, mlx.img.mlx_img);
	mlx_destroy_window(mlx.ptr_mlx, mlx.ptr_window);
	mlx_destroy_display(mlx.ptr_mlx);
	free(mlx.ptr_mlx);
	return (0);
}
