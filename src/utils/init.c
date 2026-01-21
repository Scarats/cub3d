#include "../cub3d.h"

void set_orientation(t_data *data)
{
	const char dir = data->parse.orientation;

	if (dir == 'N')
	{
		data->p.dir_angle = 90;
		data->p.v_dir = get_vector(data->p.dir_angle);
	}
	else if (dir == 'S')
	{
		data->p.dir_angle = 270;
		data->p.v_dir = get_vector(data->p.dir_angle);
	}
	else if (dir == 'E')
	{	
		data->p.dir_angle = 0;
		data->p.v_dir = get_vector(data->p.dir_angle);
	}
	else
	{
		data->p.dir_angle = 180;
		data->p.v_dir = get_vector(data->p.dir_angle);
	}
	data->p.v_plane.dx = -data->p.v_dir.dy * FOV;
	data->p.v_plane.dy = data->p.v_dir.dx * FOV;
}

void init(t_data *data)
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

	data->normal.size = 19;
	data->fire.size = 5;
	data->reload.size = 66;
	gettimeofday(&data->last_frame_time, NULL);
	data->bullets = 10;
}

void ft_init_struct(t_data *data, char *map)
{
	data->parse.file = map;
	data->parse.element = ft_split("NO-SO-WE-EA-F-C-DO", '-');
	my_array_addtolist(&data->malloc_list, (void **)data->parse.element);
	init(data);
}
