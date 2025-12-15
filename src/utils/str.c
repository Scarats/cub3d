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