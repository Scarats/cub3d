#include "../cub3d.h"

void	apply_pov(t_data *data)
{
	bool changed;

	changed = false;
	if (data->controls.look_left)
	{
		data->p.dir_angle = set_angle(data->p.dir_angle, POV);
		changed = true;
	}
	if (data->controls.look_right)
	{
		data->p.dir_angle = set_angle(data->p.dir_angle, -POV);
		changed = true;
	}
	if (data->controls.look_left || data->controls.look_right)
	{
		data->p.v_dir = get_vector(data->p.dir_angle);
		changed = true;
	}
	if (changed)
	{
		data->p.v_dir = get_vector(data->p.dir_angle);
		data->p.v_plane.dx = -data->p.v_dir.dy * FOV;
		data->p.v_plane.dy =  data->p.v_dir.dx * FOV;
	}
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
