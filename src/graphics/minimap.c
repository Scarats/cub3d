/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:20:44 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/22 12:20:45 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_big_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mini.pixel)
	{
		j = 0;
		while (j < data->mini.pixel)
		{
			my_pixel_put(data->img_buff, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_player(t_data *data)
{
	int	i;
	int	j;

	i = -data->mini.pixel / 5;
	while (i < data->mini.pixel / 5)
	{
		j = -data->mini.pixel / 5;
		while (j < data->mini.pixel / 5)
		{
			my_pixel_put(data->img_buff, (data->p.pos.x * data->mini.pixel) + i,
				(data->p.pos.y * data->mini.pixel) + j, P_RED);
			j++;
		}
		i++;
	}
}

void	ft_draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->parse.map[y])
	{
		x = 0;
		while (data->parse.map[y][x])
		{
			if (data->parse.map[y][x] == '1')
				ft_draw_big_pixel(data, x * data->mini.pixel, y
					* data->mini.pixel, P_WHITE);
			if (data->parse.map[y][x] == 'D')
				ft_draw_big_pixel(data, x * data->mini.pixel, y
					* data->mini.pixel, P_BROWN);
			x++;
		}
		y++;
	}
	ft_draw_player(data);
}
