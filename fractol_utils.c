#include "fractol.h"
#include "minilibx-linux/mlx.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	ft_error(int a, t_fractal *fractal)
{
	if (a == 2)
	{
		mlx_destroy_display(fractal->mlx_init);
		free(fractal->mlx_init);
	}
	if (a == 3)
	{
		mlx_destroy_image(fractal->mlx_init, fractal->img.img_ptr);
		mlx_destroy_display(fractal->mlx_win);
		free(fractal->mlx_init);
	}
	printf("malloc error");
	exit(EXIT_FAILURE);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_init = mlx_init();
	if (fractal->mlx_init == NULL)
		ft_error(1, NULL);
	fractal->mlx_win = mlx_new_window(fractal->mlx_init,
			WIDTH, HEIGHT, fractal->fractal_type);
	if (fractal->mlx_win == NULL)
		ft_error(2, fractal);
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_init, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
		ft_error(3, fractal);
	fractal->img.pixel_addr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp,
			&fractal->img.size_line,
			&fractal->img.endian);
	events_handler(fractal);
	data_init(fractal);
}

void	fractal_help(void)
{
	ft_putstr_fd("Which fractal would you like to view?", 1);
	ft_putstr_fd("\nM - Mandelbrot", 1);
	ft_putstr_fd("\nJ - Julia", 1);
	ft_putstr_fd("\nB - Burning Ship", 1);
	ft_putstr_fd("\nFor Julia, you may specify starting values for the\n", 1);
	ft_putstr_fd("initial fractal shape. Values must be between\n", 1);
	ft_putstr_fd("-2.0 and 2.0 and must contain a decimal point.\n", 1);
	ft_putstr_fd("usage example:\n", 1);
	ft_putstr_fd("*********************control*****************\n", 1);
	ft_putstr_fd("for shifting colors use z/x\n", 1);
	ft_putstr_fd("for deep image use f/j\n", 1);
	ft_putstr_fd("for zooming use the mouse wheel or i/o\n", 1);
	ft_putstr_fd("for movement use the arrow keyys\n", 1);
}
