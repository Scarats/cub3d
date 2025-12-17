#include "../cub3d.h"

// Compute the ray direction according to x (position on the screen) and the curr direction
void compute_ray_direction(t_player *p, int x, int width, t_vector *ray_dir)
{
	double screen_x;

	screen_x = 2.0 * x / width - 1.0;
	ray_dir->dx = p->v_dir.dx + p->v_plane.dx * screen_x;
	ray_dir->dy = p->v_dir.dy + p->v_plane.dy * screen_x;
}

void init_dda(t_dda *dda, t_player *p, t_vector *ray_dir)
{
    dda->map_pos.x = (int)p->pos.x;
    dda->map_pos.y = (int)p->pos.y;

    dda->delta_dist.x = fabs(1.0 / ray_dir->dx);
    dda->delta_dist.y = fabs(1.0 / ray_dir->dy);

    if (ray_dir->dx < 0)
    {
        dda->step.x = -1;
        dda->side_dist.x = (p->pos.x - dda->map_pos.x) * dda->delta_dist.x;
    }
    else
    {
        dda->step.x = 1;
        dda->side_dist.x = (dda->map_pos.x + 1.0 - p->pos.x) * dda->delta_dist.x;
    }

    if (ray_dir->dy < 0)
    {
        dda->step.y = -1;
        dda->side_dist.y = (p->pos.y - dda->map_pos.y) * dda->delta_dist.y;
    }
    else
    {
        dda->step.y = 1;
        dda->side_dist.y = (dda->map_pos.y + 1.0 - p->pos.y) * dda->delta_dist.y;
    }
}

void	dda_wall_detection(t_dda *dda, t_data *data, int *side)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->map_pos.x += dda->step.x;
			*side = 0;	
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->map_pos.y += dda->step.y;
			*side = 1;	
		}
		if (dda->map_pos.y < 0 || dda->map_pos.y >= data->map.height ||
            dda->map_pos.x < 0 || dda->map_pos.x >= data->map.width)
            break;
		if (data->map.map[dda->map_pos.y][dda->map_pos.x] != '0')
			hit = 1;
	}
}

void raycasting(t_data *data, t_player *p)
{
	int x;
	int side;

	x = -1;
	while (++x < data->win_width)
	{
		compute_ray_direction(p, x, data->win_width, &p->v_dir);
		init_dda(&data->dda, p, &p->v_dir);
		dda_wall_detection(&data->dda, data, &side);
		data->p.dir.x = (double)data->dda.map_pos.x * MINIMAP_SCALE;
		data->p.dir.y = (double)data->dda.map_pos.y * MINIMAP_SCALE;
	}
}