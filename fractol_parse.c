#include "fractol.h"

int	valid_arg(int ac, char **av)
{
	if ((ac == 2 && !ft_strncmp(av[1], "M", 2))
		|| ((ac == 4 || ac == 2) && !ft_strncmp(av[1], "J", 2))
		|| ((ac == 2 && ft_strlen(av[1]) == 1 && av[1][0] == 'B')))
		return (1);
	else
	{
		return (0);
	}
}

void	fractal_help(void)
{
	ft_putstr_fd("Error \n use this ./fractol M ", 1);
	ft_putstr_fd("or  ./fractol J <value_1> <value_2> or ./fractol J\n", 1);
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

void	parse_args(t_fractal *fractal, int ac, char **av)
{
	fractal->fractal_type = av[1];
	if (ac == 4 && av[1][0] == 'J')
	{
		if (!is_valid_double(av[2]) || !is_valid_double(av[3]))
		{
			fractal_help();
			exit(EXIT_FAILURE);
		}
		fractal->julia_x = str_to_double(av[2]);
		fractal->julia_y = str_to_double(av[3]);
		if ((fractal->julia_x > 2.0 || fractal->julia_x < -2.0)
			|| (fractal->julia_y > 2.0 || fractal->julia_y < -2.0))
		{
			fractal_help();
			exit(EXIT_FAILURE);
		}
	}
	fractal->ac = ac;
}
