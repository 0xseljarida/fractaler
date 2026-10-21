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

static void	complex_z(t_complex *z, double x, double y, t_fractal *fractal)
{
	double	pixel_size;

	pixel_size = 3.6 * fractal->zoom / WIDTH;
	z->x = (x + 0.5 - WIDTH * 0.5) * pixel_size + fractal->shift_x;
	z->y = (HEIGHT * 0.5 - y - 0.5) * pixel_size;
	if (fractal->fractal_type[0] == 'B')
		z->y = -z->y;
	z->y += fractal->shift_y;
}

static int	escape_color(int iteration, t_complex z, t_fractal *fractal)
{
	static const int	palette[6][3] = {
	{5, 8, 22}, {20, 42, 90}, {24, 163, 176},
	{247, 235, 189}, {229, 158, 66}, {5, 8, 22}};
	double				position;
	double				fraction;
	int					index;
	int					rgb[3];
	int					channel;

	position = iteration + 1.0 - log2(log(hypot(z.x, z.y)));
	position = position * 0.025 + fractal->colors_shift / 655360.0;
	position = (position - floor(position)) * 5.0;
	index = (int)position;
	fraction = position - index;
	channel = 0;
	while (channel < 3)
	{
		rgb[channel] = palette[index][channel] * (1.0 - fraction)
			+ palette[index + 1][channel] * fraction;
		channel++;
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static int	sample_color(t_fractal *fractal, double x, double y)
{
	t_complex	z;
	t_complex	c;
	int			i;

	complex_z(&z, x, y, fractal);
	ft_fractol_type(&z, &c, fractal);
	if (fractal->fractal_type[0] != 'J')
		z = (t_complex){0.0, 0.0};
	i = -1;
	while (++i < fractal->iterations_defintion)
	{
		if (fractal->fractal_type[0] == 'B' && fractal->ac == 2)
			z = sum_complex(power_complex(ft_absolut(z)), c);
		else
			z = sum_complex(power_complex(z), c);
		if (z.x * z.x + z.y * z.y > 256.0)
		{
			return (escape_color(i, z, fractal));
		}
	}
	return (0x070A12);
}

static int	pixel_color(t_fractal *fractal, int x, int y)
{
	int	color;
	int	r;
	int	g;
	int	b;
	int	sample;

	r = 0;
	g = 0;
	b = 0;
	sample = 0;
	while (sample < 4)
	{
		color = sample_color(fractal, x + (sample % 2) * 0.5 - 0.25,
				y + (sample / 2) * 0.5 - 0.25);
		r += (color >> 16) & 255;
		g += (color >> 8) & 255;
		b += color & 255;
		sample++;
	}
	return (((r / 4) << 16) | ((g / 4) << 8) | (b / 4));
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
			my_mlx_pixel_put(&fractal->img, x, y, pixel_color(fractal, x, y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_init,
		fractal->mlx_win, fractal->img.img_ptr, 0, 0);
}
