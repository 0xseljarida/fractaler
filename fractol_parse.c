#include "fractol.h"

#define GREEN "\x1b[32m"
#define CYAN "\x1b[1;36m"
#define RESET "\x1b[0m"

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
	ft_putstr_fd(
		"\n" CYAN "  FRACT-OL" RESET "  |  Fractal explorer\n\n"
		CYAN "  Usage\n" RESET
		"    " GREEN "./fractol M" RESET "              Mandelbrot\n"
		"    " GREEN "./fractol B" RESET "              Burning Ship\n"
		"    " GREEN "./fractol J [real imag]" RESET "  Julia\n\n"
		"    Julia parameters are optional; provide both or neither.\n"
		"    Each value must be between -2 and 2 (inclusive).\n\n"
		CYAN "  Example\n" RESET
		"    " GREEN "./fractol J -0.7 0.27" RESET "\n\n"
		CYAN "  Controls\n" RESET
		"    Arrow keys       Pan\n"
		"    Mouse wheel      Zoom\n"
		"    i / o            Zoom in / out\n"
		"    j / f            Increase / decrease iterations\n"
		"    z / x            Shift colors\n"
		"    Esc              Quit\n\n",
		2);
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
