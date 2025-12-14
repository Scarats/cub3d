#include "../cub3d.h"

// Form the prev_angle, calculate the new angle according to the pixel_pov_shift
double set_angle(double	prev_angle, double	pixel_pov_shift)
{
	static double sensitivity = -1;
	double angle;

	if (sensitivity == -1)
	{
		if (SENSITIVITY > 1)
			sensitivity = 1;
		else if (SENSITIVITY <= 0)
			sensitivity = 0.01;
		else
			sensitivity = SENSITIVITY;
	}	
	pixel_pov_shift *= sensitivity;
		
	angle = fmod(prev_angle + pixel_pov_shift, 360);
	if (angle < 0)
 	   angle += 360;
	return (angle);
}

// t_vector get_vector(t_point position, double angle)
// {
// 	t_vector vector;
// 	double rad;

// 	rad = angle * M_PI / 180.0;
// 	vector.dx = cos(rad);
// 	vector.dy = sin(rad);
// 	return (vector);
// }

// Only use for testing or drawing the minimap, it gives the direction point from the position the angle and the length.
// Currently used to draw a line for testing.
void    set_dir_from_pos(t_point *direction, t_point *position, double angle, double length)
{
    double rad;
    double dx;
    double dy;

    rad = angle * M_PI / 180.0;
    dx = cos(rad);
    dy = sin(rad);

    direction->x = position->x + (int)round(dx * length);
    direction->y = position->y - (int)round(dy * length);
}
