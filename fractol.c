#include "fractol.h"

int	valid_arg(int ac, char **av)
{
	if ((ac == 2 && ft_strlen(av[1]) == 1 && av[1][0] == 'M')
		|| ((ac == 4 || ac == 2) && (ft_strlen(av[1]) == 1 && av[1][0] == 'J')))
		return (1);
	else
	{
		return (0);
	}
}

void	ft_fractal(char **av, int ac)
{
	t_fractal	fractal;

	fractal.fractal_type = av[1];
	if (ac == 4 && av[1][0] == 'J')
	{
		fractal.julia_x = str_to_double(av[2]);
		fractal.julia_y = str_to_double(av[3]);
	}
	fractal.ac = ac;
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
		
		ft_putstr_fd("Error \n use this ./fractol M or  ./fractol J <value_1> <value_2> \n",1);
		fractal_help();
		exit(EXIT_FAILURE);
	}
}
