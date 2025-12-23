#include "../cub3d.h"

void	init(t_data *data)
{
	fdprintf(1, "init\n");
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
	data->p.v_dir.dx = 1; // facing east
	data->p.v_dir.dy = 0;
	// plane perpendicular to v_dir, scaled by FOV
	data->p.v_plane.dx = -data->p.v_dir.dy * FOV;
	data->p.v_plane.dy = data->p.v_dir.dx * FOV;

	data->normal.size = 19;
	data->fire.size = 5;
	data->reload.size = 66;
    gettimeofday(&data->last_frame_time, NULL);
	data->bullets = 10;
}

void	ft_init_struct(t_data *data, char *map)
{
	data->parse.file = map;
	data->parse.element = ft_split("NO-SO-WE-EA-F-C", '-');
	my_array_addtolist(&data->malloc_list, (void **)data->parse.element);
	init(data);
}
