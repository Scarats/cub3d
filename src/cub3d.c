#include "cub3d.h"

void hardcoded_minimap(t_data *data)
{
	printf("hardcoded_minimap\n");
	data->map.height = 4;
	data->map.width = 4;
	data->map.map = my_malloc(NULL, &data->malloc_list, sizeof(int *) * 4);
	for (int i = 0; i < 4; i++)
	{
 	   data->map.map[i] = my_malloc(NULL, &data->malloc_list, 4 * sizeof(int));
	}
	int hardcoded[4][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1}
	};

	for (int i = 0; i < 4; i++)
	{
 	   for (int j = 0; j < 4; j++)
 	   {
	      data->map.map[i][j] = hardcoded[i][j];
	    }
	}
}


// After a key is pressed, this function is used to create
// the new img according to the current situation and render it.
int	main_logic(t_data *data)
{
	if (!data || !data->img_buff || !data->img_main)
		return (perror("main_logic"), 1);
	
	mouse_edge(data);

	// TEMP ======================================
	set_dir_from_pos(&data->direction, &data->position, data->direction_angle, data->win_width / 2);	
	draw_line(data->position, data->direction, P_WHITE, data->img_buff);
	// ===========================================

	draw_minimap(data, data->map);
	refresh_images(data);
	data->curr_mouse_pos->x = -1;
	data->curr_mouse_pos->y = -1;
	return (0);
	
	
	// Raycast
	// Switch buff_img and main_img
}

void init(t_data *data)
{
	fdprintf(1, "init\n");


	// IMG
	data->img_buff = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
	init_new_img(data->img_buff, data);
	data->img_main = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
	init_new_img(data->img_main, data);

	// MOUSE POS
	data->curr_mouse_pos = my_malloc(NULL, &data->malloc_list, sizeof(t_point));
	data->last_mouse_pos = my_malloc(NULL, &data->malloc_list, sizeof(t_point));

	// MINIMAP
	hardcoded_minimap(data);
	
	// MAP TO SCREEN RATIO
	init_minimap_ratio(data);	

	get_position(data);
	set_hooks(data);
	mlx_loop_hook(data->mlx, main_logic, data);
	mlx_loop(data->mlx);
}

int main()
{
	t_data data;

	ft_memset(&data, 0, sizeof(t_data));
	// Check the map
	data.mlx = mlx_init();
	if (!data.mlx)
		return (perror("mlx"), 1);
	my_addtolist(&data.malloc_list, data.mlx);
	create_window(&data);
	init(&data);
	return (0);
}