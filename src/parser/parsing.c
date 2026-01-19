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

static void	ft_read_file(t_data *data)
{
	int		fd;
	int		bytes;
	char	str[1024];

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

static void	ft_stock_element(t_data *data, char *element, char *file)
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
	if (!ft_strncmp(element, "F", 1))
		return (ft_free_str(&data->file.floor),
			(void)(data->file.floor = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "C", 1))
		return (ft_free_str(&data->file.ceiling),
			(void)(data->file.ceiling = ft_strndup(file, siz)));
}

static void	ft_search_in_file(t_data *data)
{
	int	i;
	int	j;
	int	siz;

	i = -1;
	while (data->parse.stock[++i])
	{
		j = 0;
		while (ft_strncmp(data->parse.stock + i, data->parse.element[j],
				ft_strlen(data->parse.element[j])))
			j++;
		if (data->parse.element[j])
		{
			siz = ft_strlen(data->parse.element[j]) + i;
			while (ft_isspace(data->parse.stock[i]) || i < siz)
				data->parse.stock[i++] = ' ';
			ft_stock_element(data, data->parse.element[j], data->parse.stock
				+ i);
			while (!ft_isspace(data->parse.stock[i]))
				data->parse.stock[i++] = ' ';
		}
		else if (!ft_is_char_in_str(data->parse.stock[i], "10NSEWD\n"))
			data->parse.stock[i++] = ' ';
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
	if (ft_nbr_and_player_orientation(data) != 1)
		ft_error(&data, "💥 THERE MUST BE ONLY ONE PLAYER IN THE MAP 💥", 1);
	printf(RED "orientation = %c\n" RESET, data->parse.orientation);
	if (!ft_check_unclosed_map(data->parse.map))
		ft_error(&data, "💥 INCORRECT MAP 💥", 1);
	ft_map_size(data);
	ft_save_assets(data);
	get_sprites(data);
}
