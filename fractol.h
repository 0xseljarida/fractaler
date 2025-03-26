#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# define WIDTH 900
# define HEIGHT 900


typedef struct	s_image
{

	void *img_ptr;
	int bpp;
	int	size_line;
	int	endian;
	char *pixel_addr;
	
}				t_image;

typedef struct	s_fractal
{
	char	*fractal_type;
	void	*mlx_init;
	void	*mlx_win;
	t_image	img;
}				t_fractal;

typedef struct	s_complex
{
	double x;
	double y;
}				t_complex;

void fractal_render(t_fractal *fractal);
void	fractal_init(t_fractal *fractal);
#endif
