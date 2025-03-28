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

	events_handler(fractal);
	data_init(fractal);
}
