#include "../cub3d.h"

void	ft_draw_floor_and_celling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->win_width)
	{
		x = 0;
		while (x < data->win_height)
		{
			if (x < data->win_height / 2)
				my_pixel_put(data->img_buff, y, x, data->tex.ceiling);
			else
				my_pixel_put(data->img_buff, y, x, data->tex.floor);
			x++;
		}
		y++;
	}
}
