#include "../cub3d.h"

// Malloc the name once and overwrite it everytime.
char *build_name(char *s1, char *s2, const unsigned int size)
{
    char *str;

    if (!s1 || !s2)
        return (NULL);
    str = malloc(size + 1);
    ft_strcpy(str, s1);
    ft_strcpy((char *)(str + ft_strlen(s1)), s2);
    return (str);
}

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
    number = ft_itoa(10);
    name_len = ft_strlen(path);
    name = ft_strjoin(path, "  ");
    i = -1;
    imgs = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
    while (++i < size)
    {
        ft_strcpy((char *)(name + name_len), ft_itoa_no_malloc(number, i + 1));
        imgs[i] = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
        

        ft_memset(name, 0, name_len);
    }
    free(number);
    free(name);
    return (imgs);
}


void get_sprites(t_data *data)
{
}