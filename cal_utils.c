#include "fractol.h"

double	scale(double unscaledNum, double minAllowed, double maxAllowed, double min, double max)
{
  return (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed;
}

t_complex	sum_complex(t_complex z, t_complex c)
{
	z.x = z.x + c.x;
	z.y = z.y + c.y;
	return (z);
}

t_complex	power_complex(t_complex z)
{
	t_complex result;
	
	result.x = z.x * z.x -  z.y * z.y;
	result.y = 2 * z.y * z.x;
	return (result);
}

double str_to_double(char *str)
{
    double	result;
	double	factor;
    double	sign;
	
	result = 0.0;
	factor = 1.0;
	sign = 1.0;
    if (*str == '-')
	{
        sign = -1.0;
        str++;
    }
	else if (*str == '+')
	{
        str++;
    }

    while (*str >= '0' && *str <= '9')
	{
        result = result * 10.0 + (*str - '0');
        str++;
    }

    if (*str == '.')
	{
        str++;
        while (*str >= '0' && *str <= '9')
		{
            factor *= 0.1;
            result += (*str - '0') * factor;
            str++;
        }
    }
    return sign * result;
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s && s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	fractal_help(void)
{
	ft_putstr_fd("Which fractal would you like to view?", 1);
	ft_putstr_fd("\nM - Mandelbrot", 1);
	ft_putstr_fd("\nJ - Julia", 1);
	ft_putstr_fd("\nB - Burning Ship", 1);
	ft_putstr_fd("\nFor Julia, you may specify starting values for the\n", 1);
	ft_putstr_fd("initial fractal shape. Values must be between\n", 1);
	ft_putstr_fd("-2.0 and 2.0 and must contain a decimal point.\n", 1);
	ft_putstr_fd("usage example:\t", 1);
	ft_putstr_fd("./fractol J\n\t\t./fractol J 0.285 0.01\e[0m", 1);
}
