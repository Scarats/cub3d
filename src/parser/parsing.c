/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcardair <tcardair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:20:59 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/26 11:26:34 by tcardair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_search_in_file_b(t_data *data, int *i)
{
	if (data->parse.stock[*i]
		&& !ft_is_char_in_str(data->parse.stock[*i], "10NSEWD\n"))
		data->parse.stock[(*i)++] = ' ';
	if (data->parse.stock[*i])
		(*i)++;
}

static void	ft_search_in_file(t_data *data)
{
	int	i;
	int	j;
	int	siz;

	i = 0;
	while (data->parse.stock && data->parse.stock[i])
	{
		j = 0;
		while (ft_strncmp(data->parse.stock + i, data->parse.element[j],
				ft_strlen(data->parse.element[j])))
			j++;
		if (data->parse.stock[i] && data->parse.element[j])
		{
			siz = ft_strlen(data->parse.element[j]) + i;
			while (data->parse.stock[i]
				&& (ft_isspace(data->parse.stock[i]) || i < siz))
				data->parse.stock[i++] = ' ';
			ft_stock_element(data, data->parse.element[j],
				data->parse.stock + i);
			while (data->parse.stock[i] && !ft_isspace(data->parse.stock[i]))
				data->parse.stock[i++] = ' ';
		}
		ft_search_in_file_b(data, &i);
	}
}

void	ft_parsing_b(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->parse.map[i])
	{
		j = 0;
		while (data->parse.map[i][j])
		{
			if (data->parse.map[i][j] == '_')
				data->parse.map[i][j] = '0';
			if (data->parse.map[i][j] == 'd')
				data->parse.map[i][j] = 'D';
			j++;
		}
		i++;
	}
}

void	ft_parsing(t_data *data)
{
	printf("ft_parsing\n");
	ft_read_file(data);
	ft_search_in_file(data);
	if (!data->file.ceiling || !data->file.floor || !data->file.east
		|| !data->file.north || !data->file.south || !data->file.west)
		ft_error(&data, "💥 MISSING TEXTURE 💥", 1);
	ft_convert_color(data);
	ft_isolate_map(data);
	if (!data->parse.map)
		ft_error(&data, "💥 WRONG MAP 💥", 1);
	if (ft_nbr_and_player_orientation(data) != 1)
		ft_error(&data, "💥 THERE MUST BE ONLY ONE PLAYER IN THE MAP 💥", 1);
	if (!ft_check_unclosed_map(data->parse.map,
			(int)data->p.pos.y, (int)data->p.pos.x, 0))
		ft_error(&data, "💥 INCORRECT MAP 💥", 1);
	ft_parsing_b(data);
	ft_map_size(data);
	ft_save_assets(data);
	get_sprites(data);
}
