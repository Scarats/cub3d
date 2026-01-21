#include "../cub3d.h"

bool	ft_is_char_in_str(const char c, const char *type)
{
	int	i;

	if (!c || !type)
		return (true);
	i = 0;
	while (type[i] != '\0')
	{
		if (type[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	ft_free_str(char **str)
{
	if (!*str)
		return ;
	free(*str);
	*str = NULL;
}

void	ft_free_arr(char ***arr)
{
	int	i;

	if (!*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		ft_free_str(&(*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	ft_free_struct(t_data **s)
{
	ft_free_str(&(*s)->file.north);
	ft_free_str(&(*s)->file.south);
	ft_free_str(&(*s)->file.west);
	ft_free_str(&(*s)->file.east);
	ft_free_str(&(*s)->file.floor);
	ft_free_str(&(*s)->file.ceiling);
	ft_free_str(&(*s)->file.door);
}
