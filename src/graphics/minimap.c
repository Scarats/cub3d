#include "../cub3d.h"

void	draw_minimap(t_data *data, t_map map)
{
	int x;
	int y;

	x = -1;
	y = -1;
	while (++y < map.height)
	{
		while (++x < map.width)
		{
			if (map.map[y][x] > 0)
				draw_rectangle(x, y, map.height, map.width, data);
		}
	}

}