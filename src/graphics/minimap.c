#include "../cub3d.h"

void ft_draw_big_pixel(t_data *data, int x, int y, int pixel)
{
    int i;
    int j;

    i = 0;
    while (i < pixel)
    {
        j = 0;
        while (j < pixel)
        {
            my_pixel_put(data->img_buff, x + i, y + j, P_WHITE);
            j++;
        }
        i++;
    }
}


void ft_draw_minimap(t_data *data)
{
    int x;
    int y;
    // static int yes = 0;
    
    int width;
    int height;
    int pixel;

    if (data->parse.width >= data->parse.height)
    {
        width = (int)(data->win_width * MINI_MAP);
        height = (data->parse.height * width) / data->parse.width;
    }
    else
    {
        height = (int)(data->win_height * MINI_MAP);
        width = (data->parse.width * height) / data->parse.height;
    }
    pixel = height / data->parse.height;
    y = 0;
    while (data->parse.map[y])
    {
        x = 0;
        while (data->parse.map[y][x])
        {
            if (data->parse.map[y][x] == '1')
                ft_draw_big_pixel(data, x * pixel, y * pixel, pixel);
            // else
            // {
            //      my_pixel_put(data->img_buff, x, y, P_RED);
            //     //   printf("=%d=", data->parse.map[x][y]);
            // }
               
            x++;
        }
        y++;
    }
}
