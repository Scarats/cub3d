#include "../cub3d.h"

t_vector build_input_vectors(t_controls *dir)
{
	t_vector input;
	double len;
	
	input.dx = 0;
	input.dy = 0;

	if (dir->straight)
		input.dy += 1;
	if (dir->back)
		input.dy -= 1;
	if (dir->left)
		input.dx -= 1;
	if (dir->right)
		input.dx += 1;

	len = sqrt(input.dx * input.dx + input.dy * input.dy);
	if (len > 0)
	{
 		input.dx /= len;
 		input.dy /= len;
	}
	return (input);
}

void	set_position(t_controls *dir, t_data *data)
{
	t_vector input;
	t_vector forward;
	t_vector perpendicular;
	t_vector move;
	
	input = build_input_vectors(dir);

	if (input.dx == 0 && input.dy == 0)
		return;
	
	forward = data->v_dir;

	perpendicular.dx = -forward.dy;
	perpendicular.dy = forward.dx;

	move.dx = forward.dx * input.dy + perpendicular.dx * input.dx;
	move.dy = forward.dy * input.dy + perpendicular.dy * input.dx;

	data->position.x += move.dx * WALK_SPEED;
	data->position.y -= move.dy * WALK_SPEED;
}
