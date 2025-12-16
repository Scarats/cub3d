#include "../cub3d.h"

// Compute the ray direction according to x (position on the screen) and the curr direction
void compute_ray_direction(t_player *p, int x, int width, t_vector *ray_dir)
{
	double screen_x;

	screen_x = 2.0 * x / width - 1.0;
	ray_dir->dx = p->dir.x + p->v_plane.dx * screen_x;
	ray_dir->dy = p->dir.y + p->v_plane.dy * screen_x;
}

void	init_dda(t_dda *dda, t_player *p, t_vector *ray_dir)
{
	dda->map_pos.x = (int)p->pos.x;
	dda->map_pos.y = (int)p->pos.y;

	dda->delta_dist.x = fabs(1.0 / ray_dir->dx);
	dda->delta_dist.y = fabs(1.0 / ray_dir->dy);

	// Find the next border, either on x or y
	if (ray_dir->dx < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (p->pos.x - dda->map_pos.x) * dda->delta_dist.x;
	}
	else
	{
		dda->step.y = -1;
		dda->side_dist.y = (dda->map_pos.x + 1.0 - p->pos.x)* dda->delta_dist.y;
	}
}

void raycasting(t_data *data, t_player *p)
{
	int x;

	x = -1;
	while (++x < data->win_width)
	{
		compute_ray_direction(p, x, data->win_width, &p->dir);
		init_dda(&data->dda, p, &p->dir);

	}
}