#include "../cub3d.h"

void	render_img(t_img *img, t_data *data)
{
	if (!img)
		return (void)printf(RED "NULL IMG\n" RESET);
	mlx_put_image_to_window(data->mlx, data->window, img->mlx_img, 0, 0);
}

void	swap_images(t_img **from, t_img **to)
{
	t_img	*tmp;

	tmp = *from;
	*from = *to;
	*to = tmp;
}

void	refresh_images(t_data *data)
{
	if (!data || !data->img_buff || !data->img_main)
		return ((void)perror("refresh_images"));
	render_img(data->img_buff, data);
	swap_images(&data->img_main, &data->img_buff);
	reset_img(data->img_buff);
}
