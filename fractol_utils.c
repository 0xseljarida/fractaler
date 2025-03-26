#include "fractol.h"
#include "minilibx-linux/mlx.h"

static void	malloc_error(void)
{
	printf("malloc error");
	exit(EXIT_FAILURE);
}

static void	ft_error(int a, t_fractal *fractal)
{
	if (a == 2)
	{
		mlx_destroy_display(fractal->mlx_win);
		free(fractal->mlx_win);
	}
	if (a == 3)
	{
		mlx_destroy_image(fractal->mlx_init, fractal->img.img_ptr);
		mlx_destroy_display(fractal->mlx_win);
		free(fractal->mlx_win);
	}
	malloc_error();
}

void	fractal_init(t_fractal *fractal)
{
	// Establishes a connection to the X Server
	fractal->mlx_init = mlx_init();
	if (fractal->mlx_init == NULL) // faild check
		ft_error(1, NULL);
	// creat a new window;
	fractal->mlx_win = mlx_new_window(fractal->mlx_init,
			WIDTH, HEIGHT, fractal->fractal_type);
	if (fractal->mlx_win == NULL)
		ft_error(2, fractal);
	// buffer the image
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_init, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
		ft_error(3, fractal);
	// get image data
	fractal->img.pixel_addr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp,
			&fractal->img.size_line,
			&fractal->img.endian);
}
// fracta_render


double	scale(double unscaledNum, double minAllowed, double maxAllowed, double min, double max)
{
  return (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed;
}

t_complex	sum_complex(t_complex z, t_complex c)
{
	z.x = z.x + c.x;
	z.y = z.y + c.y;
	return (z);
}

t_complex	power_complex(t_complex z)
{
	t_complex result;
	
	result.x = pow(z.x, 2) - pow(z.y, 2);
	result.y = 2 * z.y * z.x;
	return (result);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->pixel_addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void axis_transformation(t_fractal *fractal, int x, int y)
{
	t_complex z;
	t_complex c;
	int	i;
	int	color;

	z.x = 0;
	z.y = 0;
	c.x = scale(x, -2, 1, 0, WIDTH);
	c.y = scale(y, 1.5, -1.5, 0, HEIGHT);
	i = 0;
	while (i < 60)
	{
		z = sum_complex(power_complex(z), c);
		if (hypot(z.x, z.y) > 2.0)
		{
			color = scale(i, 0x20050308,0x20FFFFFF, 0, 42);
			my_mlx_pixel_put(&fractal->img, x, y,color);
			return ;
		}
		i++;
	}
	color = 0x00000000;
	my_mlx_pixel_put(&fractal->img, x, y,color);
}

void fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			axis_transformation(fractal, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractal->mlx_init, fractal->mlx_win, fractal->img.img_ptr, 0, 0);
}
