#include "../cub3d.h"

void get_screen_dimentions(t_data *data)
{
	fdprintf(1, "get_screen_dimensions\n");
	data->win_width = 1400;
	data->win_height = 1050;
	mlx_get_screen_size(data->mlx, &data->win_width, &data->win_height);
	if (data->win_width < 200 || data->win_height < 200)
	{
		data->error = 1;
		stop(data);
	}
	
	// FOR HALF SCREEN
	// data->win_width /= 2;
}

void create_window(t_data *data)
{
	fdprintf(1, "create_window\n");
	get_screen_dimentions(data);
	data->window = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3d");
}

int close_window(int keycode, t_data *data)
{
	(void)keycode;
	mlx_destroy_window(data->mlx, data->window);
	stop(data);
	return (0);
}