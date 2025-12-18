#include "../cub3d.h"

// Set the angle according to the y shift.
// -delta is use for the direction to move normaly,
// if you move it to the left, it will look left instead of the opposite.
int	mouse_pov(int x, int y, t_data *data)
{
	static int	last_x = -1;
	int			delta;

	(void)x;
	if (!data)
		return (1);
	data->curr_mouse_pos->x = x;
	data->curr_mouse_pos->y = y;
	if (last_x == -1)
		last_x = x;
	delta = x - last_x;
	last_x = x;
	data->p.dir_angle = set_angle(data->p.dir_angle, -delta);
	data->p.v_dir = get_vector(data->p.dir_angle);
	data->p.v_plane.dx = -data->p.v_dir.dy * FOV;
	data->p.v_plane.dy = data->p.v_dir.dx * FOV;
	return (0);
}

// If mouse is on the edge of the window, it will continue to move the POV
void	mouse_edge(t_data *data)
{
	if (data->curr_mouse_pos->x == -1 && data->curr_mouse_pos->y == -1)
	{
		if (data->last_mouse_pos->x <= 0)
		{
			data->p.dir_angle = set_angle(data->p.dir_angle, POV);
			data->p.v_dir = get_vector(data->p.dir_angle);
		}
		else if (data->last_mouse_pos->x >= data->win_width - 1)
		{
			data->p.dir_angle = set_angle(data->p.dir_angle, -POV);
			data->p.v_dir = get_vector(data->p.dir_angle);
		}
		data->p.v_dir = get_vector(data->p.dir_angle);
		data->p.v_plane.dx = -data->p.v_dir.dy * FOV;
		data->p.v_plane.dy = data->p.v_dir.dx * FOV;
	}
	else
		*data->last_mouse_pos = *data->curr_mouse_pos;
}
