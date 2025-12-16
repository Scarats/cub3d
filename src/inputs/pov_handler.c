#include "../cub3d.h"

void	apply_pov(t_data *data)
{
	if (data->controls.look_left)
		data->p.dir_angle = set_angle(data->p.dir_angle, POV);
	if (data->controls.look_right)
		data->p.dir_angle = set_angle(data->p.dir_angle, -POV);
	if (data->controls.look_left || data->controls.look_right)
		data->p.v_dir = get_vector(data->p.dir_angle);
}

void	look_left(t_data *data)
{
	data->controls.look_left = true;
}

void	stop_look_left(t_data *data)
{
	data->controls.look_left = false;
}

void	look_right(t_data *data)
{
	data->controls.look_right = true;
}

void	stop_look_right(t_data *data)
{
	data->controls.look_right = false;
}
