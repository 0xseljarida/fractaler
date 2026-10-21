#include "fractol.h"

static void	zoom_at(int x, int y, t_fractal *fractal, int zoom_in)
{
	double	new_zoom;
	double	scale_delta;
	double	y_offset;

	new_zoom = fractal->zoom;
	if (zoom_in)
		new_zoom /= 1.05;
	else
		new_zoom *= 1.05;
	scale_delta = 3.6 * (fractal->zoom - new_zoom) / WIDTH;
	fractal->shift_x += (x + 0.5 - WIDTH * 0.5) * scale_delta;
	y_offset = HEIGHT * 0.5 - y - 0.5;
	if (fractal->fractal_type[0] == 'B')
		y_offset = -y_offset;
	fractal->shift_y += y_offset * scale_delta;
	fractal->zoom = new_zoom;
	fractal_render(fractal);
}

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

static int	mouse_handler(int keysym, int x, int y, t_fractal *fractal)
{
	if (keysym == Button5)
		zoom_at(x, y, fractal, 1);
	else if (keysym == Button4)
		zoom_at(x, y, fractal, 0);
	else
		return (0);
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
