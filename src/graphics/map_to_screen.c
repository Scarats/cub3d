#include "../cub3d.h"

// Turn a map point into a pixel point at the minimap ratio and add the padding
int	map_to_pixel(double	map_point, t_data *data)
{
	static int ratio = -1;

	if (ratio == -1)
		ratio = data->map_ratio;
	return((int)(map_point * ratio) + PADDING);
}

void init_map_ratio(t_data *data)
{
	int max;
	int window;
	float	scale_factor;

	if (data->map.height > data->map.width)
		max = data->map.height;
	else
		max = data->map.width;

	if (data->win_height > data->win_width)
		window = data->win_width;
	else
		window = data->win_height;
	
	scale_factor = MINIMAP_SCALE / 100.0f;
	
	data->map_ratio = (int)(window * scale_factor / max);
}