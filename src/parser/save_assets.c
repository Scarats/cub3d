/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcardair <tcardair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:13:47 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/26 12:07:01 by tcardair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_minimap_mesure(t_data *data)
{
	if (data->parse.width >= data->parse.height)
	{
		data->mini.width = data->win_width * MINI_MAP;
		data->mini.height = (data->parse.height * data->mini.width)
			/ data->parse.width;
	}
	else
	{
		data->mini.height = (int)(data->win_height * MINI_MAP);
		data->mini.width = (data->parse.width * data->mini.height)
			/ data->parse.height;
	}
	data->mini.pixel = data->mini.height / data->parse.height;
}

void	ft_save_images_b(t_data *data)
{
	data->tex.north.data = (int *)mlx_get_data_addr(data->tex.north.img,
			&data->tex.north.bpp, &data->tex.north.size,
			&data->tex.north.endian);
	data->tex.south.data = (int *)mlx_get_data_addr(data->tex.south.img,
			&data->tex.south.bpp, &data->tex.south.size,
			&data->tex.south.endian);
	data->tex.west.data = (int *)mlx_get_data_addr(data->tex.west.img,
			&data->tex.west.bpp, &data->tex.west.size, &data->tex.west.endian);
	data->tex.east.data = (int *)mlx_get_data_addr(data->tex.east.img,
			&data->tex.east.bpp, &data->tex.east.size, &data->tex.east.endian);
	if (data->tex.door.img)
		data->tex.door.data = (int *)mlx_get_data_addr(data->tex.door.img,
				&data->tex.door.bpp,
				&data->tex.door.size, &data->tex.door.endian);
}

void	ft_save_images(t_data *data)
{
	data->tex.north.img = mlx_xpm_file_to_image(data->mlx, data->file.north,
			&data->tex.north.w, &data->tex.north.h);
	data->tex.south.img = mlx_xpm_file_to_image(data->mlx, data->file.south,
			&data->tex.south.w, &data->tex.south.h);
	data->tex.west.img = mlx_xpm_file_to_image(data->mlx, data->file.west,
			&data->tex.west.w, &data->tex.west.h);
	data->tex.east.img = mlx_xpm_file_to_image(data->mlx, data->file.east,
			&data->tex.east.w, &data->tex.east.h);
	if (data->file.door == NULL && data->door_d == true)
		ft_error(&data, "💥 PAS PORTE 💥", 1);
	else if (data->file.door)
		data->tex.door.img = mlx_xpm_file_to_image(data->mlx, data->file.door,
				&data->tex.door.w, &data->tex.door.h);
	if (!data->tex.north.img || !data->tex.south.img || !data->tex.west.img
		|| !data->tex.east.img)
		ft_error(&data, "💥 FT_SAVE_ASSET 💥", 1);
	ft_save_images_b(data);
}

void	ft_save_assets(t_data *data)
{
	ft_minimap_mesure(data);
	ft_save_images(data);
}
