#include "fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_init,
					fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_init,
						fractal->mlx_win);
	mlx_destroy_display(fractal->mlx_init);
	free(fractal->mlx_init);
	exit(EXIT_SUCCESS);
}

int key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	
	else if (keysym == XK_Left)
		fractal->shift_x -= (fractal->zoom)*0.3;

	else if (keysym == XK_Right)
		fractal->shift_x += (fractal->zoom)*0.3;

	else if (keysym == XK_Up)
		fractal->shift_y += (fractal->zoom)*0.3;

	else if (keysym == XK_Down)
		fractal->shift_y -= (fractal->zoom)*0.3;

	else if (keysym == XK_i)
	{
		fractal->zoom *= 0.95;
	}
	else if (keysym == XK_o)
	{
		fractal->zoom *= 1.05;
	}
	else if (keysym == XK_j)
		fractal->iterations_defintion += 10;
	else if (keysym == XK_f)
		fractal->iterations_defintion -= 10;
	
	else if (keysym == XK_z)
		fractal->colors_shift += 0x00000100;
	else if (keysym == XK_x)
		fractal->colors_shift -= 0x00000100;
	fractal_render(fractal);
	return (1);
}

int	mouse_handler(int keysysm, int x, int y, t_fractal *fractal)
{
	else if (keysym == Button4)
		fractal->zoom += 10;
	else if (keysym == Button5)
		fractal->zoom -= 10;
	return (1);
}

void	events_handler(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_win,
			DestroyNotify,
			StructureNotifyMask,
			close_handler,
			fractal);

	mlx_hook(fractal->mlx_win,
			KeyPress,
			KeyPressMask,
			key_handler,
			fractal);
	/*
	mlx_hook(fractal_window->mlx_win,
			ButtonPress,
			ButtonPressMask,
			mouse_handler,
			fractal);
	mlx_hook(fractal->mlx_window,
			MotionNotify,
			PointerMotionMask,
			julia_track,
			fractal);
	*/
}
