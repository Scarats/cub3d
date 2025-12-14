#include "../cub3d.h"

int key_released(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		stop_look_left(data);
	else if (keycode == KEY_RIGHT)
		stop_look_right(data);
	return (0);
}

int key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		look_left(data);
	else if (keycode == KEY_RIGHT)
		look_right(data);
	else if (keycode == KEY_ESC)
		stop(data);
	return (0);
}

// Setups hook and then call the main_logic
void	set_hooks(t_data *data)
{
	fdprintf(1, "setup_hooks\n");
	mlx_hook(data->window, EVENT_KEY_PRESSED, 1L << 0, key_pressed, data);
	mlx_hook(data->window, EVENT_KEY_RELEASED, 1L << 1, key_released, data);
	mlx_hook(data->window, 17, 1L << 17, stop, data);
	mlx_hook(data->window, 6, 1L << 6, mouse_pov, data);
}