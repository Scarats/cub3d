#include "../cub3d.h"

void	go_straight(t_data *data, bool stop)
{
	if (stop)
	{
		data->controls.straight = false;
		return ;
	}
	data->controls.straight = true;
}

void	go_right(t_data *data, bool stop)
{
	if (stop)
	{
		data->controls.right = false;
		return ;
	}
	data->controls.right = true;
}

void	go_left(t_data *data, bool stop)
{
	if (stop)
	{
		data->controls.left = false;
		return ;
	}
	data->controls.left = true;
}

void	go_back(t_data *data, bool stop)
{
	if (stop)
	{
		data->controls.back = false;
		return ;
	}
	data->controls.back = true;
}
