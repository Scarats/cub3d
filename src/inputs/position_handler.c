#include "../cub3d.h"

void	go_straight(t_data *data, bool stop)
{
	printf("go_straight %d\n", stop);
	if (stop)
	{
		data->controls.straight = false;
		return ;
	}
	data->controls.straight = true;
	set_position(&data->controls, data);
}

void	go_right(t_data *data, bool stop)
{
	printf("go_right %d\n", stop);
	if (stop)
	{
		data->controls.right = false;
		return ;
	}
	data->controls.right = true;
	set_position(&data->controls, data);
}

void	go_left(t_data *data, bool stop)
{
	printf("go_left %d\n", stop);
	if (stop)
	{
		data->controls.left = false;
		return ;
	}
	data->controls.left = true;
	set_position(&data->controls, data);
}

void	go_back(t_data *data, bool stop)
{
	printf("go_back %d\n", stop);
	if (stop)
	{
		data->controls.back = false;
		return ;
	}
	data->controls.back = true;
	set_position(&data->controls, data);
}
