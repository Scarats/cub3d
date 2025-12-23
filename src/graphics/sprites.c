#include "../cub3d.h"

// Check if a color is considered transparent (white-ish)
int is_transparent(int color)
{
    int r;
    int g;
    int b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    // If all RGB components are very high (close to white), consider it transparent
    if (r >= TRANSPARENCY_THRESHOLD && g >= TRANSPARENCY_THRESHOLD 
        && b >= TRANSPARENCY_THRESHOLD)
        return (1);
    return (0);
}

void    sprites_to_screen(t_pex *img, t_data *data)
{
    t_point p;
    int color;
    int pix_per_row;
    // static t_point start = {0, 0};

    // if (start.x == 0 || start.y == 0)
    // {
    //     start.x = data->sprite_start.x;
    //     start.y = data->sprite_start.y;
    // }
    pix_per_row = img->size / (img->bpp / 8);
    p = data->sprite_start;
    p.y = PADDING;
    while (p.y < img->h)
    {
        p.x = PADDING;
        while (p.x < img->w)
        {
            color = img->data[p.y * pix_per_row + p.x];
            if (!is_transparent(color))
                my_pixel_put(data->img_buff, (p.x - PADDING) + data->sprite_start.x, (p.y - PADDING) + data->sprite_start.y, color);
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
    // Increase the counter according to the IMG_PS
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
