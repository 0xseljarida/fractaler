#include "fractol.h"

static int	key_handler(int keysym, t_fractal *fractal)
{
	switch (keysym)
	{
		case XK_Escape:
			return (close_handler(fractal));
		case XK_Left:
			fractal->shift_x -= fractal->zoom * 0.3;
			break ;
		case XK_Right:
			fractal->shift_x += fractal->zoom * 0.3;
			break ;
		case XK_Up:
			fractal->shift_y += fractal->zoom * 0.3;
			break ;
		case XK_Down:
			fractal->shift_y -= fractal->zoom * 0.3;
			break ;
		case XK_i:
			fractal->zoom /= 1.05;
			break ;
		case XK_o:
			fractal->zoom *= 1.05;
			break ;
		case XK_j:
			fractal->iterations_defintion += 10;
			break ;
		case XK_f:
			fractal->iterations_defintion -= 10;
			break ;
		case XK_z:
			fractal->colors_shift += 0x0000FF00;
			break ;
		case XK_x:
			fractal->colors_shift -= 0x0000FF00;
			break ;
		default:
			return (0);
	}
	fractal_render(fractal);
	return (1);
}

static int	mouse_handler(int keysym, t_fractal *fractal)
{
	if (keysym == Button5)
		fractal->zoom /= 1.05;
	else if (keysym == Button4)
		fractal->zoom *= 1.05;
	fractal_render(fractal);
	return (1);
}

void	events_handler(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_win, DestroyNotify,
		StructureNotifyMask,
		close_handler,
		fractal);
	mlx_hook(fractal->mlx_win, KeyPress,
		KeyPressMask,
		key_handler,
		fractal);
	mlx_hook(fractal->mlx_win, ButtonPress,
		ButtonPressMask,
		mouse_handler,
		fractal);
}
