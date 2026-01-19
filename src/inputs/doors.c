#include "../cub3d.h"

// Check if door is found in the block the player is looking at
bool check_door(t_data *data)
{
	t_dpoint	curr_pos;


	curr_pos = data->p.pos;

	if (data->parse.map[(int)curr_pos.y][(int)curr_pos.x] > '0')
		return (false);
	return (true);
}

// If door is found AND the open door flag is set to true, then open/lock the door he looks at
