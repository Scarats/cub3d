#include "../cub3d.h"

// Set the angle according to the y shift.
// -delta is use for the direction to move normaly, 
// if you move it to the left, it will look left instead of the opposite. 
int	mouse_pov(int x, int y, t_data *data)
{
	static int last_x = -1;
	int delta;

	(void)x;
	if(!data)
		return (1);

	data->curr_mouse_pos->x = x;
	data->curr_mouse_pos->y = y;

	if (last_x == -1)
		last_x = x;
	delta = x - last_x;

	last_x = x;

	data->direction_angle = set_angle(data->direction_angle, -delta);
	return (0);
}

// If mouse is on the edge of the window, it will continue to move the POV
void    mouse_edge(t_data *data)
{
	if (data->curr_mouse_pos->x == -1 && data->curr_mouse_pos->y == -1)
	{
		if (data->last_mouse_pos->x <= 0)
			data->direction_angle = set_angle(data->direction_angle, POV);
		else if (data->last_mouse_pos->x >= data->win_width - 1)
			data->direction_angle = set_angle(data->direction_angle, -POV);
	}
	else
		*data->last_mouse_pos = *data->curr_mouse_pos;
}
