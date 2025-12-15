#include "../cub3d.h"

void	go_straight(t_data *data, bool stop)
{
	if (stop)
	{
		data->controls.straight = false;
		data->controls.total -= 1;
		return ;
	}
	data->controls.straight = true;
	data->controls.total += 1;
	set_position(&data->controls, data);
}

void	go_right(t_data *data, bool stop)
{
	if (stop)
	{
		data->controls.right = false;
		data->controls.total -= 1;
		return ;
	}
	data->controls.right = true;
	data->controls.total += 1;
	set_position(&data->controls, data);
}

void	go_left(t_data *data, bool stop)
{
	if (stop)
	{
		data->controls.left = false;
		data->controls.total -= 1;
		return ;
	}
	data->controls.left = true;
	data->controls.total += 1;
	set_position(&data->controls, data);
}

void	go_back(t_data *data, bool stop)
{
	if (stop)
	{
		data->controls.back = false;
		data->controls.total -= 1;
		return ;
	}
	data->controls.back = true;
	data->controls.total += 1;
	set_position(&data->controls, data);
}
