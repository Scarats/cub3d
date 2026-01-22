/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcardair <tcardair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:20:21 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/22 13:33:45 by tcardair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	compute_hit_point(t_player *player, t_dda *dda, int side,
// 		t_dpoint *hit_point, t_vector *ray_dir)
// {
// 	double	distance;

// 	if (side == 0)
// 		distance = dda->side_dist.x - dda->delta_dist.x;
// 	else
// 		distance = dda->side_dist.y - dda->delta_dist.y;
// 	hit_point->x = player->pos.x + ray_dir->dx * distance;
// 	hit_point->y = player->pos.y + ray_dir->dy * distance;
// }

double	get_distance(int side, t_dda *dda)
{
	if (side == 0)
		return (dda->side_dist.x - dda->delta_dist.x);
	else
		return (dda->side_dist.y - dda->delta_dist.y);
}

void	raycasting_b(t_data *data, t_vector	ray_dir)
{
	if (data->dda.is_door)
		data->parse.orientation = 'D';
	else if (data->side == 0)
	{
		if (ray_dir.dx > 0)
			data->parse.orientation = 'E';
		else
			data->parse.orientation = 'W';
	}
	else
	{
		if (ray_dir.dy > 0)
			data->parse.orientation = 'S';
		else
			data->parse.orientation = 'N';
	}
}

void	raycasting(t_data *data, t_player *p)
{
	int			x;
	t_vector	ray_dir;
	double		distance;

	x = -1;
	while (++x < data->win_width)
	{
		compute_ray_direction(p, x, data->win_width, &ray_dir);
		init_dda(&data->dda, p, &ray_dir);
		dda_wall_detection(&data->dda, data, &data->side);
		raycasting_b(data, ray_dir);
		distance = get_distance(data->side, &data->dda);
		draw_wall(x, distance, data, ray_dir);
	}
}
