#include "../cub3d.h"

void	destroy_image(t_img *img, t_data *data)
{
	if (img->mlx_img)
	{
		mlx_destroy_image(data->mlx, img->mlx_img);
		img->mlx_img = NULL;
	}
}

// Free the allocated memory and exit the program using the error number.
int	stop(t_data **data)
{
	int	error;

	fdprintf(1, "stop\n");
	error = (*data)->error;
	if ((*data)->img_buff)
		destroy_image((*data)->img_buff, *data);
	if ((*data)->img_main)
		destroy_image((*data)->img_main, *data);
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

void	ft_error(t_data **s, const char *str, int code)
{
	(*s)->error = code;
	if (str)
		printf("%s\n", str);
	stop(s);
}
