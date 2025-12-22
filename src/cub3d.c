#include "cub3d.h"

// After a key is pressed, this function is used to create
// the new img according to the current situation and render it.
int	main_logic(t_data *data)
{
	if (!data || !data->img_buff || !data->img_main)
		return (perror("main_logic"), 1);
	set_position(&data->controls, data);
	mouse_edge(data);
	apply_pov(data);
	ft_draw_floor_and_celling(data);
	raycasting(data, &data->p);
	// draw_sprites(data);
	sprites_handler(&data->normal, data);
	ft_draw_minimap(data);
	refresh_images(data);
	data->curr_mouse_pos->x = -1;
	data->curr_mouse_pos->y = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	printf("start cub3\n");
	if (argc != 2)
		return (printf("💥 PLEASE ENTER ONLY ONE .cub FILE 💥\n"), 1);
	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = mlx_init();
	if (!data->mlx)
		return (perror("mlx"), 1);
	my_addtolist(&data->malloc_list, data->mlx);
	get_screen_dimentions(data);
	ft_init_struct(data, argv[1]);
	ft_parsing(data);
	create_window(data);
	set_hooks(data);
	mlx_loop_hook(data->mlx, main_logic, data);
	mlx_loop(data->mlx);
	stop(&data);
	return (0);
}
