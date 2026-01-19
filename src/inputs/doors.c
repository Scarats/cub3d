#include "../cub3d.h"

// Check if door is found in the block the player is looking at
void handle_door(t_data *data)
{
	t_dpoint	block;
	double check_dist;
	char		door;

	check_dist = 0.5;

	block = data->p.pos;
	
	// Early return if player is on an open door (undefined behavior)
	if (data->parse.map[(int)block.y][(int)block.x] == 'O')
		return ;

	block.x += data->p.v_dir.dx * check_dist;
	block.y += data->p.v_dir.dy * check_dist;

	door = data->parse.map[(int)block.y][(int)block.y];

	if (door == 'D' && data->door)
		data->parse.map[(int)block.y][(int)block.x] = 'O';
	else if (door == 'O' && data->door)
		data->parse.map[(int)block.y][(int)block.x] = 'D';
}

// If door is found AND the open door flag is set to true, then open/lock the door he looks at
