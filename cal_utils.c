#include "fractol.h"

double	scale(double unscalednum, double minallowed,
		double maxallowed, double max)
{
	double	min;

	min = 0;
	return ((maxallowed - minallowed)
		* (unscalednum - min) / (max - min) + minallowed);
}

t_complex	sum_complex(t_complex z, t_complex c)
{
	z.x = z.x + c.x;
	z.y = z.y + c.y;
	return (z);
}

t_complex	power_complex(t_complex z)
{
	t_complex	result;

	result.x = z.x * z.x - z.y * z.y;
	result.y = 2 * z.y * z.x;
	return (result);
}

t_complex	ft_absolut(t_complex z)
{
	z.x = fabs(z.x);
	z.y = fabs(z.y);
	return (z);
}
