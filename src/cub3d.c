#include "cub3d.h"

// After a key is pressed, this function is used to create
// the new img according to the current situation and render it.
int	main_logic(t_data *data)
{
	if (!data || !data->img_buff || !data->img_main)
		return (perror("main_logic"), 1);
	apply_pov(data);
	set_position(&data->controls, data);
	mouse_edge(data);
	draw_player(data);
	printf(RED"dir (%f, %f)\n"RESET, data->v_dir.dx, data->v_dir.dy);
	printf(ORANGE"(%f, %f)\n"RESET, data->position.x, data->position.y);
	// draw_minimap(data, data->map);
	refresh_images(data);
	data->curr_mouse_pos->x = -1;
	data->curr_mouse_pos->y = -1;
	return (0);
	// Raycast
	// Switch buff_img and main_img
}

void	init(t_data *data)
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
	// MAP TO SCREEN RATIO
    static char row0[] = {1,1,1,1};
    static char row1[] = {1,0,0,1};
    static char row2[] = {1,0,0,1};
    static char row3[] = {1,1,1,1};
    static char *table[] = { row0, row1, row2, row3 };

    data->map.map = table;
    data->map.height = 4;
    data->map.width = 4;
	
	data->position.x = 50;
	data->position.y = 50;
	data->v_dir.dx = 1;
	data->v_dir.dy = 1;
	set_hooks(data);
	mlx_loop_hook(data->mlx, main_logic, data);
	mlx_loop(data->mlx);
}

int	main(void)
{
	t_data data;

	ft_memset(&data, 0, sizeof(t_data));
	// Check the map
	data.mlx = mlx_init();
	if (!data.mlx)
		return (perror("mlx"), 1);
	// ft_parsing(&data);
	my_addtolist(&data.malloc_list, data.mlx);
	create_window(&data);
	init(&data);
	return (0);
}