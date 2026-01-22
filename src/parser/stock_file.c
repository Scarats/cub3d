/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcardair <tcardair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:35:18 by tcardair          #+#    #+#             */
/*   Updated: 2026/01/22 13:37:32 by tcardair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*ft_stock_file(char *stock, char *str)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(stock) + ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (stock && stock[i])
		new[j++] = stock[i++];
	i = 0;
	while (str && str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	ft_free_str(&stock);
	return (new);
}

void	ft_read_file(t_data *data)
{
	int		fd;
	int		bytes;
	char	str[1024];

	fd = ft_strlen(data->parse.file) - 4;
	if (fd > 0 && ft_strcmp(data->parse.file + fd, ".cub"))
		ft_error(&data, "💥 WRONG FILE NAME 💥", 1);
	fd = open(data->parse.file, O_RDONLY);
	if (fd == -1)
		ft_error(&data, "💥 FILE DOES'NT EXIST 💥", 1);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, str, 1023);
		if (bytes <= 0)
			break ;
		str[bytes] = '\0';
		data->parse.stock = ft_stock_file(data->parse.stock, str);
		if (!data->parse.stock)
			return (close(fd), ft_error(&data, "💥 MALLOC FT_STOCK_MAP 💥", 1));
	}
	close(fd);
	my_addtolist(&data->malloc_list, data->parse.stock);
}

static void	ft_stock_element_b(t_data *data, char *element, char *file, int siz)
{
	if (!ft_strncmp(element, "F", 1))
		return (ft_free_str(&data->file.floor),
			(void)(data->file.floor = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "C", 1))
		return (ft_free_str(&data->file.ceiling),
			(void)(data->file.ceiling = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "DO", 1))
		return (ft_free_str(&data->file.door),
			(void)(data->file.door = ft_strndup(file, siz)));
}

void	ft_stock_element(t_data *data, char *element, char *file)
{
	int	siz;

	siz = 0;
	while (file[siz] && !ft_isspace(file[siz]))
		siz++;
	if (!ft_strncmp(element, "NO", 2))
		return (ft_free_str(&data->file.north),
			(void)(data->file.north = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "SO", 2))
		return (ft_free_str(&data->file.south),
			(void)(data->file.south = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "WE", 2))
		return (ft_free_str(&data->file.west),
			(void)(data->file.west = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "EA", 2))
		return (ft_free_str(&data->file.east),
			(void)(data->file.east = ft_strndup(file, siz)));
	ft_stock_element_b(data, element, file, siz);
}
