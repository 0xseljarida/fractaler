#include "fractol.h"

static void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->pixel_addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	ft_fractol_type(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (fractal->fractal_type[0] == 'J' && fractal->ac == 4)
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else if (fractal->fractal_type[0] == 'J' && fractal->ac == 2)
	{
		c->x = -0.8;
		c->y = +0.156;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

void	complex_z(t_complex *z, int x, int y, t_fractal *fractal)
{
	if (fractal->fractal_type[0] == 'B' && fractal->ac == 2)
	{
		z->x = scale(x, -2, 2, WIDTH) * fractal->zoom + fractal->shift_x;
		z->y = scale(y, -1.5, 1.5, HEIGHT) * fractal->zoom + fractal->shift_y;
	}
	else
	{
		z->x = scale(x, -2, 2, WIDTH) * fractal->zoom + fractal->shift_x;
		z->y = scale(y, 1.5, -1.5, HEIGHT) * fractal->zoom + fractal->shift_y;
	}
}

static void	axis_transformation(t_fractal *fractal, int x, int y)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	complex_z(&z, x, y, fractal);
	ft_fractol_type(&z, &c, fractal);
	i = -1;
	while (++i < fractal->iterations_defintion)
	{
		if (fractal->fractal_type[0] == 'B' && fractal->ac == 2)
			z = sum_complex(power_complex(ft_absolut(z)), c);
		else
			z = sum_complex(power_complex(z), c);
		if (z.x * z.x + z.y * z.y > 4.0)
		{
			color = scale(i, 0x00FF0000 + fractal->colors_shift,
					0x0000FF00 + fractal->iterations_defintion,
					fractal->iterations_defintion);
			my_mlx_pixel_put(&fractal->img, x, y, color);
			return ;
		}
	}
	color = 0x00000000;
	my_mlx_pixel_put(&fractal->img, x, y, color);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			axis_transformation(fractal, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_init,
		fractal->mlx_win, fractal->img.img_ptr, 0, 0);
}
