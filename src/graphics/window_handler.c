/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:20:28 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/22 12:20:34 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_screen_dimentions(t_data *data)
{
	fdprintf(1, "get_screen_dimensions\n");
	data->win_width = 1400;
	data->win_height = 1050;
	mlx_get_screen_size(data->mlx, &data->win_width, &data->win_height);
	if (data->win_width < 200 || data->win_height < 200)
	{
		data->error = 1;
		stop(&data);
	}
}

void	create_window(t_data *data)
{
	fdprintf(1, "create_window\n");
	data->window = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"cub3d");
}
