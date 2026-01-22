/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcardair <tcardair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:28:23 by tcardair          #+#    #+#             */
/*   Updated: 2026/01/22 13:34:37 by tcardair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Compute the ray direction according to
// x (position on the screen) and the curr direction
void	compute_ray_direction(t_player *p, int x, int width, t_vector *ray_dir)
{
	double	screen_x;

	screen_x = 2.0 * x / width - 1.0;
	ray_dir->dx = p->v_dir.dx + p->v_plane.dx * screen_x;
	ray_dir->dy = p->v_dir.dy + p->v_plane.dy * screen_x;
}

void	init_dda_b(t_dda *dda, t_player *p, t_vector *ray_dir)
{
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
	init_dda_b(dda, p, ray_dir);
}

void	dda_wall_detection_b(t_dda *dda, t_data *data, int *hit)
{
	char	cell;

	cell = data->parse.map[dda->map_pos.y][dda->map_pos.x];
	if (cell == '1')
		*hit = 1;
	else if (cell == 'D')
	{
		dda->is_door = 1;
		*hit = 1;
	}
}

void	dda_wall_detection(t_dda *dda, t_data *data, int *side)
{
	int		hit;

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
		dda_wall_detection_b(dda, data, &hit);
	}
}
