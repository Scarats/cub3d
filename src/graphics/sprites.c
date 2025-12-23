#include "../cub3d.h"

void    sprites_to_screen(t_pex *img, t_data *data)
{
    t_point p;
    int color;
    int pix_per_row;

    pix_per_row = img->size / (img->bpp / 8);
    p = data->sprite_start;
    p.x = 0;
    p.y = 0;
    while (p.y < img->h)
    {
        p.x = 0;
        while (p.x < img->w)
        {
            color = img->data[p.y * pix_per_row + p.x];
            my_pixel_put(data->img_buff, p.x, p.y, color);
            p.x++;
        }
        p.y++;
    }
}

void    sprites_handler(t_sprite *s, t_data *data)
{
    if (s->counter >= s->size)
        s->counter = 0;
    sprites_to_screen(s->frames[s->counter], data);
    s->counter++; 
}

// void    draw_sprites(t_data *data)
// {
//     if (data->flag_fire || data->flag_reload)
//     {
//         if (data->flag_fire)
//         {
//             sprites_handler(&data->fire, &data);
//             if (data->fire.counter == 0)
//                 data->flag_fire = 0;
//         }
//         else
//         {
//             sprites_handler(&data->reload, &data);
//             if (data->reload.counter == 0)
//                 data->flag_reload = 0;
//         }
//     }
//     else
//         sprites_to_screen(&data->normal, &data);
// }
