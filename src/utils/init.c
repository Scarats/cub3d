#include "../cub3d.h"

void	init(t_data *data)
{
	static char	row0[] = {1, 1, 1, 1};
	static char	row1[] = {1, 0, 0, 1};
	static char	row2[] = {1, 0, 0, 1};
	static char	row3[] = {1, 1, 1, 1};
	static char	*table[] = {row0, row1, row2, row3};

	fdprintf(1, "init\n");
	// IMG
	data->img_buff = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
	init_new_img(data->img_buff, data);
	data->img_main = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
	init_new_img(data->img_main, data);
	// MOUSE POS
	data->curr_mouse_pos = my_malloc(NULL, &data->malloc_list, sizeof(t_point));
	data->last_mouse_pos = my_malloc(NULL, &data->malloc_list, sizeof(t_point));
	// MAP TO SCREEN RATIO
	data->map.map = table;
	data->map.height = 4;
	data->map.width = 4;
	data->p.pos.x = 50;
	data->p.pos.y = 50;
	data->p.v_dir.dx = 1;
	data->p.v_dir.dy = 1;
}

void	ft_init_struct(t_data *data, char *map)
{
	data->parse.file = map;
	data->parse.stock = NULL;
	data->parse.element = NULL;
	data->parse.element = ft_split("NO-SO-WE-EA-F-C", '-');
	if (!data->parse.element)
		ft_error(&data, "💥 DATA->PARSE.ELEMENTS FT_INIT_STRUCT 💥", 1);
	data->parse.map = NULL;
	data->file.north = NULL;
	data->file.south = NULL;
	data->file.west = NULL;
	data->file.east = NULL;
	data->file.floor = NULL;
	data->file.ceiling = NULL;
	init(data);
}
