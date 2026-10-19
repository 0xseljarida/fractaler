#include "fractol.h"

static void	ft_fractal(char **av, int ac)
{
	t_fractal	fractal;

	parse_args(&fractal, ac, av);
	fractal_init(&fractal);
	fractal_render(&fractal);
	mlx_loop(fractal.mlx_init);
}

int	main(int ac, char **av)
{
	if (valid_arg(ac, av) == 1)
		ft_fractal(av, ac);
	else
	{
		fractal_help();
		exit(EXIT_FAILURE);
	}
}
