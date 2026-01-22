/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_define.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:33:49 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/22 15:14:10 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_map_size(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->parse.width = 0;
	data->parse.height = 0;
	while (data->parse.map[i])
	{
		j = 0;
		while (data->parse.map[i][j])
			j++;
		while (j > 0 && data->parse.map[i][j - 1] != '1')
			j--;
		data->parse.map[i][j] = '\0';
		if (j > data->parse.width)
			data->parse.width = j;
		i++;
	}
	data->parse.height = i;
}

bool	ft_check_unclosed_map(char **map, int x, int y)
{
	int		len;
	bool	is_closed;

	len = 0;
	while (map[x][len])
		len++;
	if (x < 0 || !map[x] || y < 0 || y >= len || map[x][y] == '\n')
		return (false);
	if (map[x][y] == '1' || map[x][y] == '_' || map[x][y] == 'd')
		return (true);
	if (map[x][y] == 'D')
		map[x][y] = 'd';
	if (map[x][y] != '1' && map[x][y] != 'd')
		map[x][y] = '_';
	is_closed = true;
	is_closed &= ft_check_unclosed_map(map, x + 1, y);
	is_closed &= ft_check_unclosed_map(map, x, y + 1);
	is_closed &= ft_check_unclosed_map(map, x - 1, y);
	is_closed &= ft_check_unclosed_map(map, x, y - 1);
	is_closed &= ft_check_unclosed_map(map, x + 1, y + 1);
	is_closed &= ft_check_unclosed_map(map, x + 1, y - 1);
	is_closed &= ft_check_unclosed_map(map, x - 1, y + 1);
	is_closed &= ft_check_unclosed_map(map, x - 1, y - 1);
	return (is_closed);
}

int	ft_nbr_and_player_orientation(t_data *data)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	data->parse.orientation = '\0';
	while (data->parse.map[i])
	{
		j = 0;
		while (data->parse.map[i][j])
		{
			if (ft_is_char_in_str(data->parse.map[i][j], "NSEW"))
			{
				data->p.pos.x = j;
				data->p.pos.y = i;
				data->parse.orientation = data->parse.map[i][j];
				data->parse.map[i][j] = '0';
				cnt++;
			}
			j++;
		}
		i++;
	}
	return (cnt);
}

void	ft_isolate_map(t_data *data)
{
	int		siz;
	int		start;
	char	*map;

	start = 0;
	siz = ft_strlen(data->parse.stock);
	while (data->parse.stock[start] && data->parse.stock[start] != '1')
		start++;
	while (start > 0 && data->parse.stock[start] != '\n')
		start--;
	while (siz > 0 && data->parse.stock[siz] != '1')
		siz--;
	siz++;
	if (siz <= start || ft_strlen(data->parse.stock) + start <= siz - start)
		return ;
	map = ft_strndup(data->parse.stock + start, siz - start);
	if (!map)
		return ;
	data->parse.map = ft_split(map, '\n');
	my_array_addtolist(&data->malloc_list, (void **)data->parse.map);
	free(map);
}

void	ft_convert_color(t_data *data)
{
	int		i;
	char	**tmp;

	i = 0;
	while (data->file.ceiling[i] >= '0' && data->file.ceiling[i] <= '9')
		i++;
	tmp = ft_split(data->file.ceiling, data->file.ceiling[i]);
	if (!tmp[0] || !tmp[1] || !tmp[2])
		return (ft_free_arr(&tmp), ft_error(&data, "💥 WRONG CEILING 💥", 1));
	data->tex.ceiling = ((0xFF << 24)
			| (ft_atoi(tmp[0]) << 16)
			| (ft_atoi(tmp[1]) << 8) | ft_atoi(tmp[2]));
	ft_free_arr(&tmp);
	i = 0;
	while (data->file.floor[i] >= '0' && data->file.floor[i] <= '9')
		i++;
	tmp = ft_split(data->file.floor, data->file.floor[i]);
	if (!tmp[0] || !tmp[1] || !tmp[2])
		return (ft_free_arr(&tmp), ft_error(&data, "💥 WRONG FLOOR 💥", 1));
	data->tex.floor = ((0xFF << 24)
			| (ft_atoi(tmp[0]) << 16)
			| (ft_atoi(tmp[1]) << 8) | ft_atoi(tmp[2]));
	ft_free_arr(&tmp);
}
