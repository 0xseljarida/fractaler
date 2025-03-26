#include "fractal.h"

void	handle_events(&fractal)
{
	mlx_hook(fractal->mlx_win, int x_event, int x_mask, 
		 int (*funct)(),void *param)
}
