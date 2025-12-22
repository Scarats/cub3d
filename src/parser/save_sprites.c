#include "../cub3d.h"

// if !name it init and allocate name
// number is the size for malloc, the max file_number
// if name it changes the file number
// number is the file_number
char *build_name(char *name, char *path, int number)
{
	int path_size;
	int total_size;
	
	path_size = ft_strlen(path);
	if (!name)
	{
		total_size = sizeof(char) * (path_size + size_in_char(number) + 4);
		name = malloc(total_size + 1);
		ft_memset(name, 0, total_size);
		name[total_size] = '\0';
		ft_strcpy(name, path);
		return (name);
	}
	(void)total_size;
	ft_itoa_no_malloc(&name[path_size], number);
	path_size = ft_strlen(name);
	ft_strcpy(&name[path_size], ".xpm");
	return (name);
}

// Save an array of t_img with this kinda name : "path/to/file_"
// After the "_" comes the number. The function will import up to "size"
// The name is rebuilt using "  .xpm", the 2 spaces are for file number.
// WARNING: the file number has to be < 99, or add the according amount of spaces.
t_img **save_sprites(t_data *data, char *path, const unsigned int size)
{
    unsigned int i;
    t_img **imgs;
    char *name;

	if (!data || !path || size <= 0)
		return (NULL);
	name = NULL;
	name = build_name(name, path, size);
	i = -1;
    imgs = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
    while (++i < size)
    {
		name = build_name(name, path, i + 1);
		printf("file %s\n", name);
        imgs[i] = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
        imgs[i]->mlx_img = mlx_xpm_file_to_image(data->mlx, name, &imgs[i]->w, &imgs[i]->h);
        if (!imgs[i]->mlx_img)
            return (free(name), NULL);
        imgs[i]->addr = mlx_get_data_addr(imgs[i]->mlx_img, &imgs[i]->bits_per_pixel, &imgs[i]->line_length, &imgs[i]->endian);
    }
    free(name);
    return (imgs);
}

void get_sprites(t_data *data)
{
	printf("Start sprites\n");
    data->normal.frames = save_sprites(data, "../assets/sprites/normal/normal_", 22);
    if (!data->normal.frames)
        return (ft_error(&data, "normal_sprites", 1));
    data->fire.frames = save_sprites(data, "../assets/sprites/fire/fire_", 5);
    if (!data->fire.frames)
        return (ft_error(&data, "fire_sprites", 1));
    data->reload.frames = save_sprites(data, "../assets/sprites/reload/reload_", 62);
    if (!data->reload.frames)
		return (ft_error(&data, "reload_sprites", 1));
	printf("End sprites\n");
}