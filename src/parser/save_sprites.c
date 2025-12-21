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
    name = ft_strjoin(path, "  ");
    number = name + name_len;
    i = -1;
    imgs = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
    while (++i < size)
    {
        ft_itoa_no_malloc(number, i + 1);
        imgs[i] = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
        

        ft_memset(number, 0, 2);
    }
    free(name);
    return (imgs);
}


void get_sprites(t_data *data)
{
}