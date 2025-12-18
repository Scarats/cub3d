#include "../cub3d.h"

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
	// ft_free_str(&(*s)->parse.stock);
	ft_free_arr(&(*s)->parse.element);
	ft_free_arr(&(*s)->parse.map);
	ft_free_str(&(*s)->file.north);
	ft_free_str(&(*s)->file.south);
	ft_free_str(&(*s)->file.west);
	ft_free_str(&(*s)->file.east);
	ft_free_str(&(*s)->file.floor);
	ft_free_str(&(*s)->file.ceiling);
	free(*s);
	*s = NULL;
}
