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
	dda->is_door = 0;
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
	char	cell;

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
		// if (data->parse.map[dda->map_pos.y][dda->map_pos.x] != '0' && data->parse.map[dda->map_pos.y][dda->map_pos.x] != 'O')
		// 	hit = 1;
		cell = data->parse.map[dda->map_pos.y][dda->map_pos.x];

		if (cell == '1')
			hit = 1;
		else if (cell == 'D')
		{
			dda->is_door = 1;
			hit = 1;
		}
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

void	draw_wall(int x, double distance, t_data *data, int side,
		t_vector ray_dir)
{
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	t_pex	*current_tex;

	draw_start = -(data->win_height / distance) / 2 + data->win_height / 2;
	draw_end = (data->win_height / distance) / 2 + data->win_height / 2;
	//
	if (data->parse.orientation == 'D')
		current_tex = &data->tex.door;
	//
	else if (data->parse.orientation == 'N') // Nord
		current_tex = &data->tex.north;
	else if (data->parse.orientation == 'S') // Sud
		current_tex = &data->tex.south;
	else if (data->parse.orientation == 'W') // Ouest
		current_tex = &data->tex.west;
	else
		current_tex = &data->tex.east;
	if (side == 0)
		wall_x = (data->p.pos.y + distance * ray_dir.dy);
	else
		wall_x = (data->p.pos.x + distance * ray_dir.dx);
	tex_x = (int)((wall_x - floor(wall_x)) * (double)current_tex->w);
	if (tex_x < 0)
		tex_x = 0;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end > data->win_width)
		draw_end = data->win_width;

	if (tex_x >= current_tex->w)
		tex_x = current_tex->w - 1;
	while (draw_start <= draw_end)
	{
		tex_y = (((draw_start * 256 - data->win_height * 128 + (data->win_height
							/ distance) * 128) * current_tex->h)
				/ (data->win_height / distance)) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= current_tex->h)
			tex_y = current_tex->h - 1;
		my_pixel_put(data->img_buff, x, draw_start, current_tex->data[tex_y
			* (current_tex->size / 4) + tex_x]);
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
		// MANAGE THE ORIENTATION (find the value in s_file)
		//
		if (data->dda.is_door)
			data->parse.orientation = 'D';
		//
		else if (side == 0)
		{
			if (ray_dir.dx > 0)
				data->parse.orientation = 'E'; // Est
			else
				data->parse.orientation = 'W'; // Ouest
		}
		else
		{
			if (ray_dir.dy > 0)
				data->parse.orientation = 'S'; // Sud
			else
				data->parse.orientation = 'N'; // Nord
		}
		//
		distance = get_distance(side, &data->dda);
		draw_wall(x, distance, data, side, ray_dir);
	}
}
