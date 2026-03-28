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

static int	clamp(int v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

static int	get_color(int i, int max_iter, double shift, t_complex z)
{
	double	t;
	double	phase;
	double	log_zn;
	double	smooth;
	int		r;
	int		g;
	int		b;

	log_zn = log(z.x * z.x + z.y * z.y) / 2.0;
	smooth = i + 1 - log(log_zn) / log(2.0);
	if (smooth < 0.0)
		smooth = 0.0;
	t = smooth / (double)max_iter;
	phase = shift * 0.000005;
	r = clamp((int)(127.5 + 127.5 * cos(6.2831853 * (5.0 * t + phase))));
	g = clamp((int)(127.5 + 127.5 * cos(6.2831853 * (5.0 * t + phase + 0.333))));
	b = clamp((int)(127.5 + 127.5 * cos(6.2831853 * (5.0 * t + phase + 0.667))));
	return ((r << 16) | (g << 8) | b);
}

static void	axis_transformation(t_fractal *fractal, int x, int y)
{
	t_complex	z;
	t_complex	c;
	int			i;

	complex_z(&z, x, y, fractal);
	ft_fractol_type(&z, &c, fractal);
	i = -1;
	while (++i < fractal->iterations_defintion)
	{
		if (fractal->fractal_type[0] == 'B' && fractal->ac == 2)
			z = sum_complex(power_complex(ft_absolut(z)), c);
		else
			z = sum_complex(power_complex(z), c);
		if (z.x * z.x + z.y * z.y > 256.0)
		{
			my_mlx_pixel_put(&fractal->img, x, y,
				get_color(i, fractal->iterations_defintion,
					fractal->colors_shift, z));
			return ;
		}
	}
	my_mlx_pixel_put(&fractal->img, x, y, 0x00000000);
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
