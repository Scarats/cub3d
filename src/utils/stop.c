#include "../cub3d.h"

void destroy_image(void **img, t_data *data)
{
	if (img && *img)
	{
		mlx_destroy_image(data->mlx, *img);
		*img = NULL;
	}
}

void free_sprites(t_data *data)
{
	unsigned int i;

	printf("free_sprites\n");
	i = -1;
	while (++i < data->normal.size)
		destroy_image(&data->normal.frames[i]->img, data);
	i = -1;
	while (++i < data->fire.size)
		destroy_image(&data->fire.frames[i]->img, data);
	i = -1;
	while (++i < data->reload.size)
		destroy_image(&data->reload.frames[i]->img, data);
}

// Free the allocated memory and exit the program using the error number.
int stop(t_data **data)
{
	int error;

	fdprintf(1, "stop\n");
	error = (*data)->error;
	if ((*data)->saved_sprites == 1)
		free_sprites(*data);
	ft_free_struct(data);
	if ((*data)->img_buff)
		destroy_image(&(*data)->img_buff->mlx_img, *data);
	if ((*data)->img_main)
		destroy_image(&(*data)->img_main->mlx_img, *data);
	if ((*data)->tex.north.img)
		destroy_image(&(*data)->tex.north.img, *data);
	if ((*data)->tex.east.img)
		destroy_image(&(*data)->tex.east.img, *data);
	if ((*data)->tex.south.img)
		destroy_image(&(*data)->tex.south.img, *data);
	if ((*data)->tex.west.img)
		destroy_image(&(*data)->tex.west.img, *data);
	if ((*data)->tex.door.img)
		destroy_image(&(*data)->tex.door.img, *data);
	if ((*data)->window)
	{
		mlx_destroy_window((*data)->mlx, (*data)->window);
		(*data)->window = NULL;
	}
	if ((*data)->mlx)
	{
		mlx_destroy_display((*data)->mlx);
		(*data)->mlx = NULL;
	}
	my_free(&(*data)->malloc_list);
	ft_memset(*data, 0, sizeof(t_data));
	free(*data);
	exit(error);
}

void ft_error(t_data **s, const char *str, int code)
{
	(*s)->error = code;
	if (str)
		printf("%s\n", str);
	stop(s);
}
