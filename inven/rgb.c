#include <mlx.h>
#include <stdio.h>
typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_data;

# define W 1523
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * 4 * W + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, W, W, "Hello world!");

    img.img = mlx_new_image(mlx, W, W);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    int x = 0;
    int y = 0;
	int a = 0x00000100;
    unsigned int color = 0x00FF0000;
	int	i = 0;

    while (x < W)
    {
        y = 0;
        while (y < W)
        {
            my_mlx_pixel_put(&img, x, y, color);
            y++;
        }
		printf("%d->%X\n",i++,color);
        x++;
		if (color == 0x00FFFF00)//(255,255,0)
		{
			a = -0x00010000;//(-1,0,0)
		}
		if (color == 0x0000FF00)
		{
			a = 0x00000001;
		}
		if (color == 0x0000FFFF)
		{
			a = -0x00000100;
		}
		if (color == 0x000000FF)
		{
			a = 0x00010000;
		}
		if (color == 0x00FF00FF)
			a = -0x00000001;
		color += a;
    }

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}

