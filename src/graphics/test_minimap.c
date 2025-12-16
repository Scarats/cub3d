#include "../cub3d.h"

int minimap_tile_size(t_data *data, t_map map, double map_fraction)

void draw_minimap(t_data *data, t_map *map)
{
    int tx, ty;             // tile coords
    int px, py;             // pixel coords for drawing
	static int radius = (MINIMAP_SCALE / 2) > 1 ? (MINIMAP_SCALE / 2) : 1;

    if (!data || !map || !map->map)
        return;

    for (ty = 0; ty < map->height; ++ty)
    {
        for (tx = 0; tx < map->width; ++tx)
        {
            if (map->map[ty][tx] == 1)
            {
                px = PADDING + tx * MINIMAP_SCALE;
                py = PADDING + ty * MINIMAP_SCALE;
                draw_point(data->img_buff, px, py, P_WHITE, radius);
            }
        }
    }
}