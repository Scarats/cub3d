#include "../cub3d.h"

// Malloc the name once and overwrite it everytime.
char *build_name(char *s1, char *s2, const unsigned int size)
{
    char *str;

    if (!s1 || !s2)
        return (NULL);
    str = malloc(size + 1);
    ft_strcpy(str, s1);
    ft_strcpy(&str + ft_strlen(s1), s2);
}

// Make a function that returns an array of t_img
t_img **save_sprites(t_data *data, char *path, const unsigned int size)
{
    int i;
    t_img **imgs;
    char *name;

    if (!data || !path || size <= 0)
        return (NULL);
    i = -1;
    imgs = my_malloc(NULL, &data->malloc_list, sizeof(t_img));
    while (++i < size)
    {
        imgs[i] = my_malloc(NULL, &data->malloc_list, sizeof(t_img));    
        // Memset the name everytime
    }
    free(name);
}


void get_sprites(t_data *data)
{

}