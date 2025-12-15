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

static void	ft_read_file(t_data *s)
{
	int		fd;
	int		bytes;
	char	str[1024];

	fd = open(s->parse.file, O_RDONLY);
	if (fd == -1)
		ft_error(&s, "💥 FILE DOES'NT EXIST 💥", 1);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, str, 1023);
		if (bytes <= 0)
			break ;
		str[bytes] = '\0';
		s->parse.stock = ft_stock_file(s->parse.stock, str);
		if (!s->parse.stock)
			return (close(fd), ft_error(&s, "💥 MALLOC FT_STOCK_MAP 💥", 1));
	}
	close(fd);
}

static void	ft_stock_element(t_data *s, char *element, char *file)
{
	int	siz;

	siz = 0;
	while (file[siz] && !ft_isspace(file[siz]))
		siz++;
	if (!ft_strncmp(element, "NO", 2))
		return (ft_free_str(&s->file.north),
			(void)(s->file.north = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "SO", 2))
		return (ft_free_str(&s->file.south),
			(void)(s->file.south = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "WE", 2))
		return (ft_free_str(&s->file.west),
			(void)(s->file.west = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "EA", 2))
		return (ft_free_str(&s->file.east),
			(void)(s->file.east = ft_strndup(file, siz)));
	if (!ft_strncmp(element, "F", 1))
		return (ft_free_str(&s->file.floor),
			(void)(s->file.floor = ft_strndup(file, siz), ','));
	if (!ft_strncmp(element, "C", 1))
		return (ft_free_str(&s->file.ceiling),
			(void)(s->file.ceiling = ft_strndup(file, siz), ','));
}

static void	ft_search_in_file(t_data *s)
{
	int	i;
	int	j;
	int	siz;

	i = 0;
	while (s->parse.stock[i])
	{
		j = 0;
		while (ft_strncmp(s->parse.stock + i, s->parse.element[j],
				ft_strlen(s->parse.element[j])))
			j++;
		if (s->parse.element[j])
		{
			siz = ft_strlen(s->parse.element[j]) + i;
			while (ft_isspace(s->parse.stock[i]) || i < siz)
				s->parse.stock[i++] = ' ';
			ft_stock_element(s, s->parse.element[j], s->parse.stock + i);
			while (!ft_isspace(s->parse.stock[i]))
				s->parse.stock[i++] = ' ';
		}
		else if (!ft_is_char_in_str(s->parse.stock[i], "1NSEWD\n"))
			s->parse.stock[i++] = ' ';
		else
			i++;
	}
}

void	ft_parsing(t_data *s)
{
	ft_read_file(s);
	ft_search_in_file(s);
	if (!s->file.ceiling || !s->file.floor || !s->file.east || !s->file.north
		|| !s->file.south || !s->file.west)
		ft_error(&s, "💥 MISSING TEXTURE 💥", 1);
	// ft_convert_color(s);
	ft_isolate_map(s);
	if (ft_nbr_and_player_orientation(s) != 1)
		ft_error(&s, "💥 THERE MUST BE ONLY ONE PLAYER IN THE MAP 💥", 1);
	// if (!ft_check_unclosed_map(s->parse.map, s->player.posx, s->player.posy))
	// 	ft_error(&s, "💥 INCORRECT MAP 💥", 1);
	ft_map_size(s);
	for (int i = 0; s->parse.map[i]; i++)
		printf("+%s+\n", s->parse.map[i]);
}
