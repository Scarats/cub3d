#include "cub3d.h"

void	draw_player(t_data *data)
{
	int x = data->position.x * 10;
	int y = data->position.y * 10;
	// t_point mouse = (data->curr_mouse_pos->x == -1 || data->curr_mouse_pos->y == -1) ? *data->last_mouse_pos : *data->curr_mouse_pos;
	t_dpoint dir;
	set_dir_from_pos(&dir, &data->position, data->direction_angle, 50);
	draw_d_line((t_dpoint){x, y}, dir, P_WHITE, data->img_buff);
}

// After a key is pressed, this function is used to create
// the new img according to the current situation and render it.
int	main_logic(t_data *data)
{
	if (!data || !data->img_buff || !data->img_main)
		return (perror("main_logic"), 1);
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
	// init_minimap_ratio(data);
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