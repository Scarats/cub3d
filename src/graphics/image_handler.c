/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:20:57 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/22 12:22:02 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// initialize the given image.
void	init_new_img(t_img *img, t_data *data)
{
	fdprintf(1, "init_new_img\n");
	if (!img || !data)
		return ((void)perror("init_new_img"));
	ft_memset(img, 0, sizeof(t_img));
	img->data = data;
	img->mlx_img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

// Erase all the pixels of an image.
// Will later just print the sky and ground instead of NULL
void	reset_img(t_img *img)
{
	static int		size;
	static t_data	*data;

	size = -1;
	data = NULL;
	if (!data)
		data = img->data;
	if (size == -1)
		size = img->line_length * data->win_height;
	ft_memset(img->addr, 0, size);
}
