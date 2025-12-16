#include "../cub3d.h"

void	look_left(t_data *data)
{
	data->controls.look_left = true;
	data->direction_angle = set_angle(data->direction_angle, POV);
	data->v_dir = get_vector(data->direction_angle);
}

void	stop_look_left(t_data *data)
{
	data->controls.look_left = false;
}

void	look_right(t_data *data)
{
	data->controls.look_right = true;
	data->direction_angle = set_angle(data->direction_angle, -POV);
	data->v_dir = get_vector(data->direction_angle);
}

void	stop_look_right(t_data *data)
{
	data->controls.look_right = false;
}
