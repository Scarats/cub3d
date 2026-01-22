/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcardair <tcardair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:32:07 by tcardair          #+#    #+#             */
/*   Updated: 2026/01/22 13:34:45 by tcardair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_pex	*draw_wall_b(t_data *data, double distance)
{
	t_pex	*current_tex;

	data->draw_start = -(data->win_height / distance)
		/ 2 + data->win_height / 2;
	data->draw_end = (data->win_height / distance) / 2 + data->win_height / 2;
	if (data->parse.orientation == 'D')
		current_tex = &data->tex.door;
	else if (data->parse.orientation == 'N')
		current_tex = &data->tex.north;
	else if (data->parse.orientation == 'S')
		current_tex = &data->tex.south;
	else if (data->parse.orientation == 'W')
		current_tex = &data->tex.west;
	else
		current_tex = &data->tex.east;
	return (current_tex);
}

int	draw_wall_c(t_data *data, double *wall_x, t_pex	*current_tex)
{
	int		tex_x;

	tex_x = (int)((*wall_x - floor(*wall_x)) * (double)current_tex->w);
	if (tex_x < 0)
		tex_x = 0;
	if (data->draw_start < 0)
		data->draw_start = 0;
	if (data->draw_end > data->win_width)
		data->draw_end = data->win_width;
	if (tex_x >= current_tex->w)
		tex_x = current_tex->w - 1;
	return (tex_x);
}

void	draw_wall(int x, double distance, t_data *data,
		t_vector ray_dir)
{
	int		tex_x;
	int		tex_y;
	double	wall_x;
	t_pex	*current_tex;

	current_tex = draw_wall_b(data, distance);
	if (data->side == 0)
		wall_x = (data->p.pos.y + distance * ray_dir.dy);
	else
		wall_x = (data->p.pos.x + distance * ray_dir.dx);
	tex_x = draw_wall_c(data, &wall_x, current_tex);
	while (data->draw_start <= data->draw_end)
	{
		tex_y = (((data->draw_start * 256 - data->win_height
						* 128 + (data->win_height / distance)
						* 128) * current_tex->h)
				/ (data->win_height / distance)) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= current_tex->h)
			tex_y = current_tex->h - 1;
		my_pixel_put(data->img_buff, x, data->draw_start,
			current_tex->data[tex_y * (current_tex->size / 4) + tex_x]);
		data->draw_start++;
	}
}
