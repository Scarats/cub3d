#include "../cub3d.h"

// Make a function that returns an array of t_img
t_img **save_sprites(t_data *data, char *path, const unsigned int size)
{
    int i;
    t_img **imgs;
    char *name;
    char *number;
    int name_len;

    if (!data || !path || size <= 0)
        return (NULL);
    name_len = ft_strlen(path);
    name = ft_strjoin(path, "  .xpm");
    number = name[name_len];
    i = -1;
    imgs = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
    while (++i < size)
    {
        ft_itoa_no_malloc(number, i + 1);
        imgs[i] = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
        imgs[i]->mlx_img = mlx_xpm_file_to_image(data->mlx, name, imgs[i]->w, imgs[i]->h);
        if (!imgs[i]->mlx_img)
            return (free(name), NULL);
        imgs[i]->addr = mlx_get_data_addr(imgs[i]->mlx_img, imgs[i]->bits_per_pixel, imgs[i]->line_length, imgs[i]->endian);
        ft_memset(number, 0, 2);
    }
    free(name);
    return (imgs);
}

void get_sprites(t_data *data)
{
    data->normal = save_sprites(data, "../assets/sprites/normal/normal_", 22);
    if (!data->normal)
        return (perror("normal_sprites"), stop(&data));
    data->fire = save_sprites(data, "../assets/sprites/fire/fire_", 5);
        return (perror("fire_sprites"), stop(&data));
    data->reload = save_sprites(data, "../assets/sprites/reload/reload_", 62);
        return (perror("reload_sprites"), stop(&data));
}