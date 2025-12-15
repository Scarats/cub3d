#include "../cub3d.h"

void	one_direction(t_controls *dir)
{

}

void	two_directions(t_controls *dir)
{
	if (dir->straight && dir->left)
	{
		
	}
}

void	set_position(t_controls *dir)
{
	if (dir->total == 1)
		one_direction(dir);
	else if (dir->total == 2)
		two_directions(dir);
}
