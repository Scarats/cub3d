#include "../cub3d.h"

// if action == 1 it init and allocate name
// size is for malloc
// if action == 0 it changes the file number
// size is the length of the path
char *build_name(char *name, char *path, int size, char action)
{
	int path_size;

	if (action == 1)
	{
		name = malloc(sizeof(char) * (size + size_in_char(size) + 1));
		name[sizeof(char) * (size + size_in_char(size) + 1)] = '\0';
		path_size = ft_strlen(path);
		name = ft_strcpy()
	}
	else
		path_size = size;
	ft_strcpy(name, );

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
    char *number;
    int name_len;

    if (!data || !path || size <= 0)
        return (NULL);
	name_len = ft_strlen(path);
	name = malloc(sizeof(char) * (name_len + ft_strlen(ft_itoa_no_malloc(size)));
    name = ft_strjoin(path, "  .xpm");
    number = &name[name_len];
    i = -1;
    imgs = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
    while (++i < size)
    {
        ft_itoa_no_malloc(number, i + 1);
		printf("file %s\n", name);
        imgs[i] = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
        imgs[i]->mlx_img = mlx_xpm_file_to_image(data->mlx, name, &imgs[i]->w, &imgs[i]->h);
        if (!imgs[i]->mlx_img)
            return (free(name), NULL);
        imgs[i]->addr = mlx_get_data_addr(imgs[i]->mlx_img, &imgs[i]->bits_per_pixel, &imgs[i]->line_length, &imgs[i]->endian);
        ft_memset(number, 0, 2);
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