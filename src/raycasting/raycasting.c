#include "../cub3d.h"

// Compute the ray direction according to x (position on the screen) and the curr direction
void	compute_ray_direction(t_player *p, int x, int width, t_vector *ray_dir)
{
	double	screen_x;

	screen_x = 2.0 * x / width - 1.0;
	ray_dir->dx = p->v_dir.dx + p->v_plane.dx * screen_x;
	ray_dir->dy = p->v_dir.dy + p->v_plane.dy * screen_x;
}

void	init_dda(t_dda *dda, t_player *p, t_vector *ray_dir)
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
		dda->side_dist.x = (dda->map_pos.x + 1.0 - p->pos.x)
			* dda->delta_dist.x;
	}
	if (ray_dir->dy < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (p->pos.y - dda->map_pos.y) * dda->delta_dist.y;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = (dda->map_pos.y + 1.0 - p->pos.y)
			* dda->delta_dist.y;
	}
}

void	dda_wall_detection(t_dda *dda, t_data *data, int *side)
{
	int	hit;

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
		if (dda->map_pos.y < 0 || dda->map_pos.y >= data->parse.height
			|| dda->map_pos.x < 0 || dda->map_pos.x >= data->parse.width)
			break ;
		if (data->parse.map[dda->map_pos.y][dda->map_pos.x] != '0')
			hit = 1;
	}
}

void	compute_hit_point(t_player *player, t_dda *dda, int side,
		t_dpoint *hit_point, t_vector *ray_dir)
{
	double	distance;

	if (side == 0)
		distance = dda->side_dist.x - dda->delta_dist.x;
	else
		distance = dda->side_dist.y - dda->delta_dist.y;
	hit_point->x = player->pos.x + ray_dir->dx * distance;
	hit_point->y = player->pos.y + ray_dir->dy * distance;
}

double	get_distance(int side, t_dda *dda)
{
	if (side == 0)
		return (dda->side_dist.x - dda->delta_dist.x);
	else
		return (dda->side_dist.y - dda->delta_dist.y);
}

void	draw_wall(int x, double distance, t_data *data, int side)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	static int	height = -1;

	if (height == -1)
		height = data->win_height;
	line_height = (int)(height / distance);
	draw_start = -line_height / 2 + height / 2;
	draw_end = line_height / 2 + height / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= height)
		draw_end = height - 1;
	while (draw_start <= draw_end)
	{
		if (side == 0)
			my_pixel_put(data->img_buff, x, draw_start, P_PURPLE);
		else
			my_pixel_put(data->img_buff, x, draw_start, P_ORANGE);
		draw_start++;
	}
}

void	raycasting(t_data *data, t_player *p)
{
	int			x;
	int			side;
	t_vector	ray_dir;
	double		distance;

	x = -1;
	while (++x < data->win_width)
	{
		compute_ray_direction(p, x, data->win_width, &ray_dir);
		init_dda(&data->dda, p, &ray_dir);
		dda_wall_detection(&data->dda, data, &side);
		distance = get_distance(side, &data->dda);
		draw_wall(x, distance, data, side);
	}
}
