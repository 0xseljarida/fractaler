#include "fractol.h"

int	valid_arg(int ac, char **av)
{
	if ((ac == 2 && av[1][0] == 'M'))
		return (1);
	else
		return (0);
}

void	ft_fractal(char **av)
{
	t_fractal fractal;

	fractal.fractal_type = av[1];
	fractal_init(&fractal);
	fractal_render(&fractal);
	mlx_loop(fractal.mlx_init);
}

int main(int ac, char **av)
{
	if (valid_arg(ac, av) == 1)
		ft_fractal(av);
	else
	{
		printf("Errsdr");
		exit(EXIT_FAILURE);
	}
}
