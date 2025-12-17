#include "../cub3d.h"

void	init(t_data *data)
{
	fdprintf(1, "init\n");
	// // Use chars '0'/'1' so raycasting checks against '0' work
	// static char	row0[] = "1111";
	// static char	row1[] = "1001";
	// static char	row2[] = "1001";
	// static char	row3[] = "1111";
	// static char	*table[] = {row0, row1, row2, row3};

	// data->map.height = 1;
	// data->map.width = 1;

	// IMG
	data->img_buff = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
	init_new_img(data->img_buff, data);
	data->img_main = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
	init_new_img(data->img_main, data);
	// MOUSE POS
	data->curr_mouse_pos = my_malloc(NULL, &data->malloc_list, sizeof(t_point));
	data->last_mouse_pos = my_malloc(NULL, &data->malloc_list, sizeof(t_point));
	data->curr_mouse_pos->x = 1;
	data->curr_mouse_pos->y = 1;

	// MAP TO SCREEN RATIO
	data->p.pos.x = 2;
	data->p.pos.y = 2;
	data->p.dir_angle = 0;
	data->p.v_dir.dx = 1;      // facing east
	data->p.v_dir.dy = 0;
	// plane perpendicular to v_dir, scaled by FOV
	data->p.v_plane.dx = -data->p.v_dir.dy * FOV;
	data->p.v_plane.dy =  data->p.v_dir.dx * FOV;
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
