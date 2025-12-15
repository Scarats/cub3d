#include "../cub3d.h"

void	ft_map_size(t_main *s)
{
	int	i;
	int	j;

	i = 0;
	s->parse.width = 0;
	s->parse.height = 0;
	while (s->parse.map[i])
	{
		j = 0;
		while (s->parse.map[i][j])
		{
			if (s->parse.map[i][j] == '0')
				s->parse.map[i][j] = ' ';
			j++;
		}
		while (s->parse.map[i][j] != '1')
			j--;
		s->parse.map[i][j + 1] = '\0';
		if (j > s->parse.width)
			s->parse.width = j;
		i++;
	}
	s->parse.height = i - 1;
}

bool	ft_check_unclosed_map(char **map, int x, int y)
{
	if (x < 0 || y < 0 || map[x] == NULL || map[x][y] == '\0')
		return (false);
	if (map[x][y] == '1' || map[x][y] == '0')
		return (true);
	if (map[x][y] != 'D')
		map[x][y] = '0';
	return (ft_check_unclosed_map(map, x + 1, y) && ft_check_unclosed_map(map, x
			- 1, y) && ft_check_unclosed_map(map, x, y + 1)
		&& ft_check_unclosed_map(map, x, y - 1) && ft_check_unclosed_map(map, x
			+ 1, y + 1) && ft_check_unclosed_map(map, x - 1, y - 1)
		&& ft_check_unclosed_map(map, x + 1, y - 1)
		&& ft_check_unclosed_map(map, x - 1, y + 1));
}

int	ft_nbr_and_player_orientation(t_main *s)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	s->parse.orientation = '\0';
	while (s->parse.map[i])
	{
		j = 0;
		while (s->parse.map[i][j])
		{
			if (ft_is_char_in_str(s->parse.map[i][j], "NSEW"))
			{
				s->player.posx = j;
				s->player.posy = i;
				s->parse.orientation = s->parse.map[i][j];
				s->parse.map[i][j] = '0';
				cnt++;
			}
			j++;
		}
		i++;
	}
	return (cnt);
}

void	ft_isolate_map(t_main *s)
{
	int		siz;
	int		start;
	char	*map;

	start = 0;
	siz = ft_strlen(s->parse.stock);
	while (s->parse.stock[start] && s->parse.stock[start] != '1')
		start++;
	while (start > 0 && s->parse.stock[start] != '\n')
		start--;
	while (siz > 0 && s->parse.stock[siz] != '1')
		siz--;
	siz++;
	map = ft_strndup(s->parse.stock + start, siz - start);
	s->parse.map = ft_split(map, '\n');
	ft_free_str(&map);
}

void	ft_convert_color(t_main *s)
{
	int		i;
	char	**tmp;

	i = 0;
	while (s->file.ceiling[i] >= '0' && s->file.ceiling[i] <= '9')
		i++;
	tmp = ft_split(s->file.ceiling, s->file.ceiling[i]);
	s->image.ceiling = ((0xFF << 24) | (ft_atoi(tmp[0]) << 16) | (ft_atoi(tmp[1]) << 8) | ft_atoi(tmp[2]));
	ft_free_arr(&tmp);
	i = 0;
	while (s->file.floor[i] >= '0' && s->file.floor[i] <= '9')
		i++;
	tmp = ft_split(s->file.floor, s->file.floor[i]);
	s->image.floor = ((0xFF << 24) | (ft_atoi(tmp[0]) << 16) | (ft_atoi(tmp[1]) << 8) | ft_atoi(tmp[2]));
	ft_free_arr(&tmp);
}
