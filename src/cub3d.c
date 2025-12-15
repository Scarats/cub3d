#include "cub3d.h"

void	ft_error(t_data **s, const char *str, int code)
{
	(*s)->error = code;
	if (str)
		printf("%s\n", str);
	stop(s);
}

// After a key is pressed, this function is used to create
// the new img according to the current situation and render it.
int	main_logic(t_data *data)
{
	if (!data || !data->img_buff || !data->img_main)
		return (perror("main_logic"), 1);
	mouse_edge(data);
	draw_minimap(data, data->map);
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
	init_minimap_ratio(data);
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
	ft_parsing(&data);
	my_addtolist(&data.malloc_list, data.mlx);
	create_window(&data);
	init(&data);
	return (0);
}