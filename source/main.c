#include "cub3d.h"

char		**map = NULL;
float		PlayerX = 0.0f;
float		PlayerY = 0.0f;
float		PlayerA = 0.0f;
int			ScreenWidth = 1080;
int			ScreenHeight = 720;
float		FOV = PI / 4;
float		MDepth = 0.0f;
bool		gofront = false;
bool		goback = false;
bool		goleft = false;
bool		goright = false;
bool		lookleft = false;
bool		lookright = false;
int			Pixls = 0;
char		*file_path = NULL;

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

int	color_interpolation(float color1, float color2, float dist)
{
	int	color3;

	if (dist >= MDepth)
		return (color2);
	color3 = (int)(color1 * ((MDepth - dist) / (MDepth - 0.1f)) + color2
			* ((dist - 0.1f) / (MDepth - 0.1f)));
	return (color3);
}

int	color_interpolation_rgb(int color1, int color2, float dist)
{
	int	colorrgb1[3];
	int	colorrgb2[3];
	int	colorrgb3[3];

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

void	go_front(float n)
{
	PlayerX += sinf(PlayerA) * n;
	PlayerY += cosf(PlayerA) * n;
	if (map[(int)PlayerY][(int)PlayerX] == '1')
	{
		PlayerX -= sinf(PlayerA) * n;
		PlayerY -= cosf(PlayerA) * n;
	}
}

void	go_back(float n)
{
	PlayerX -= sinf(PlayerA) * n;
	PlayerY -= cosf(PlayerA) * n;
	if (map[(int)PlayerY][(int)PlayerX] == '1')
	{
		PlayerX += sinf(PlayerA) * n;
		PlayerY += cosf(PlayerA) * n;
	}
}

void	go_left(float n)
{
	PlayerX -= cosf(PlayerA) * n;
	PlayerY += sinf(PlayerA) * n;
	if (map[(int)PlayerY][(int)PlayerX] == '1')
	{
		PlayerX += cosf(PlayerA) * n;
		PlayerY -= sinf(PlayerA) * n;
	}
}

void	go_right(float n)
{
	PlayerX += cosf(PlayerA) * n;
	PlayerY -= sinf(PlayerA) * n;
	if (map[(int)PlayerY][(int)PlayerX] == '1')
	{
		PlayerX -= cosf(PlayerA) * n;
		PlayerY += sinf(PlayerA) * n;
	}
}

int	xpm_color(t_mlx *mlx, float x, float y)
{
	int			pixelx;
	int			pixely;
	int const	*addresse;

	pixelx = mlx->wall.width * x;
	pixely = mlx->wall.height * y;
	addresse = (int *)mlx->wall.addr;
	return (addresse[mlx->wall.width * pixely + pixelx]);
}

float	side_ray(float distanceToWall, float PlayerX, float PlayerY, float eyeX,
		float eyeY)
{
	int	x;
	int	y;

	x = (int)(PlayerX + eyeX * (distanceToWall - 0.01f));
	y = (int)(PlayerY + eyeY * (distanceToWall - 0.01f));
	if (x != ((int)(PlayerX + eyeX * distanceToWall)))
	{
		if (x < ((int)(PlayerX + eyeX * distanceToWall)))
			return (1.0f - ((PlayerY + eyeY * distanceToWall) - (int)(PlayerY
						+ eyeY * distanceToWall)));
		else
			return ((PlayerY + eyeY * distanceToWall) - (int)(PlayerY + eyeY
					* distanceToWall));
	}
	if (y < ((int)(PlayerY + eyeY * distanceToWall)))
		return ((PlayerX + eyeX * distanceToWall) - (int)(PlayerX + eyeX
				* distanceToWall));
	return (1.0f - ((PlayerX + eyeX * distanceToWall) - (int)(PlayerX + eyeX
				* distanceToWall)));
}

static int	*get_color(char letter, char *arg)
{
	int		fd;
	int		*rgb;
	char	*line;
	bool	color_found;
	int		i;
	char	**s_rgb;
	int		y;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (perror("Failed to open file"), NULL);
	i = 0;
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
		return (perror("malloc failed"), NULL);
	color_found = false;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (color_found == true)
		{
			free(line);
			break ;
		}
		if (line[0] == letter && line[1] == ' ' && ft_isdigit(line[2]))
		{
			color_found = true;
			while (line[i])
			{
				s_rgb = ft_split(line + 2, ',');
				rgb[R] = ft_atoi(s_rgb[R]);
				rgb[G] = ft_atoi(s_rgb[G]);
				rgb[B] = ft_atoi(s_rgb[B]);
				y = 0;
				while (s_rgb[y])
				{
					free(s_rgb[y]);
					y++;
				}
				free(s_rgb);
				i++;
			}
		}
		free(line);
	}
	close(fd);
	return (rgb);
}

int	init_colors(t_config *config, char *arg)
{
	config->ceiling_color = get_color('C', arg);
	config->floor_color = get_color('F', arg);
	// printf("Ceiling color\nR %d\nG %d\nB %d\n\n", config->ceiling_color[R],
	// 		config->ceiling_color[G], config->ceiling_color[B]);
	// printf("Floor color\nR %d\nG %d\nB %d\n\n", config->floor_color[R],
	// 		config->floor_color[G], config->floor_color[B]);
	return (0);
}

int	rgb_to_hex(int *rgb)
{
	return ((rgb[R] & 0xff) << 16) + ((rgb[G] & 0xff) << 8) + (rgb[B] & 0xff);
}

int	trace_into_image(t_mlx *mlx, char **map)
{
	float		rayangle;
	float		distanceToWall;
	float		eyeX;
	float		eyeY;
	int			testX;
	int			testY;
	int			ceiling;
	int			floor;
	float		texturevalue;
	float		b;
	t_config	config;
	int			HitWall;

	init_colors(&config, file_path);
	for (int x = Pixls; x < ScreenWidth; x += 2)
	{
		rayangle = (PlayerA - FOV / 2) + ((float)x / (float)ScreenWidth) * FOV;
		distanceToWall = 0.0f;
		HitWall = false;
		eyeX = sinf(rayangle);
		eyeY = cosf(rayangle);
		while (HitWall == 0)
		{
			distanceToWall += 0.01f;
			testX = (int)(PlayerX + eyeX * distanceToWall);
			testY = (int)(PlayerY + eyeY * distanceToWall);
			if (testX < 0 || testX >= MDepth || testY < 0 || testY >= MDepth)
			{
				HitWall = 1;
				distanceToWall = MDepth;
			}
			else
			{
				if (map[testY][testX] == '1')
				{
					HitWall = 1;
				}
			}
		}
		ceiling = (float)(ScreenHeight / 2.0) - ScreenHeight
			/ ((float)distanceToWall);
		floor = ScreenHeight - ceiling;
		texturevalue = side_ray(distanceToWall, PlayerX, PlayerY, eyeX, eyeY);
		for (int y = 0; y < ScreenHeight; y++)
		{
			if (y < ceiling)
			{
				b = 1.0f - (y - ScreenHeight / 2.0f) / (ScreenHeight / 2.0f);
				img_pix_put(&mlx->img, x, y,
						color_interpolation_rgb(rgb_to_hex(config.ceiling_color),
							0x000000, (b / 3.0f) * MDepth));
			}
			else if (y <= floor)
				img_pix_put(&mlx->img, x, y,
						color_interpolation_rgb(xpm_color(mlx, texturevalue,
								(float)(y - ceiling) / (float)(floor
									- ceiling)), 0x000000, distanceToWall));
			else
			{
				b = 1.0f - (y - ScreenHeight / 2.0f) / (ScreenHeight / 2.0f);
				img_pix_put(&mlx->img, x, y,
						color_interpolation_rgb(rgb_to_hex(config.floor_color),
							0x000000, b * MDepth));
			}
		}
	}
	free(config.ceiling_color);
	free(config.floor_color);
	if (Pixls == 0)
		Pixls = 1;
	else
		Pixls = 0;
	return (0);
}

int	ft_loop(t_mlx *mlx)
{
	if (lookleft == 1)
		PlayerA -= 0.03f;
	if (lookright == 1)
		PlayerA += 0.03f;
	if (goleft == 1)
		go_left(0.08f);
	if (goright == 1)
		go_right(0.08f);
	if (gofront == 1)
		go_front(0.08f);
	if (goback == 1)
		go_back(0.08f);
	trace_into_image(mlx, map);
	mlx_put_image_to_window(mlx->ptr_mlx, mlx->ptr_window, mlx->img.mlx_img, 0,
			0);
	// printf("Player Angle:	%f	Player X:	%f	Player Y:	%f\n", PlayerA,
	// PlayerX, PlayerY);
	return (0);
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
	else if (keysym == XK_Left)
		lookleft = true;
	else if (keysym == XK_Right)
		lookright = true;
	else if (keysym == 'w')
		gofront = true;
	else if (keysym == 'a')
		goleft = true;
	else if (keysym == 's')
		goback = true;
	else if (keysym == 'd')
		goright = true;
	// else
		// ft_printf("Key: %d\n", keysym);
	return (0);
}

int	ft_key_release(int keysym, t_mlx *mlx)
{
	(void)mlx;
	(void)keysym;
	if (keysym == XK_Left)
		lookleft = false;
	else if (keysym == XK_Right)
		lookright = false;
	else if (keysym == 'w')
		gofront = false;
	else if (keysym == 'a')
		goleft = false;
	else if (keysym == 's')
		goback = false;
	else if (keysym == 'd')
		goright = false;
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac < 2)
		return (printf("Usage: %s <file>.cub\n", av[0]), 0);
	file_path = av[1];
	init_map(file_path);
	// printf("%f %f %f\n", PlayerX, PlayerY, PlayerA);
	for (int i = 0; map[i]; i++)
		printf("%d:	%ld:	%s\n", i, ft_strlen(map[i]), map[i]);
	mlx.ptr_mlx = mlx_init();
	mlx.ptr_window = mlx_new_window(mlx.ptr_mlx, ScreenWidth, ScreenHeight,
			"cub");
	mlx.img.mlx_img = mlx_new_image(mlx.ptr_mlx, ScreenWidth, ScreenHeight);
	mlx.img.addr = mlx_get_data_addr(mlx.img.mlx_img, &mlx.img.bpp,
			&mlx.img.line_len, &mlx.img.endian);
	mlx.wall.mlx_img = mlx_xpm_file_to_image(mlx.ptr_mlx,
												"./assets/cobblestone.xpm",
												&mlx.wall.width,
												&mlx.wall.height);
	if (mlx.wall.mlx_img == NULL)
	{
		mlx_destroy_image(mlx.ptr_mlx, mlx.img.mlx_img);
		mlx_destroy_window(mlx.ptr_mlx, mlx.ptr_window);
		mlx_destroy_display(mlx.ptr_mlx);
		free(map);
		free(mlx.ptr_mlx);
		exit(0);
	}
	mlx.wall.addr = mlx_get_data_addr(mlx.wall.mlx_img, &mlx.wall.bpp,
			&mlx.wall.line_len, &mlx.wall.endian);
	trace_into_image(&mlx, map);
	mlx_put_image_to_window(mlx.ptr_mlx, mlx.ptr_window, mlx.img.mlx_img, 0, 0);
	mlx_loop_hook(mlx.ptr_mlx, &ft_loop, &mlx);
	mlx_hook(mlx.ptr_window, KeyPress, KeyPressMask, &ft_key_press, &mlx);
	mlx_hook(mlx.ptr_window, KeyRelease, KeyReleaseMask, &ft_key_release, &mlx);
	mlx_loop(mlx.ptr_mlx);
	mlx_destroy_display(mlx.ptr_mlx);
	free(map);
	free(mlx.ptr_mlx);
	return (0);
}
