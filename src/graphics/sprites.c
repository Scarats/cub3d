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
    static int pix_per_row = 0;

    if (pix_per_row == 0)
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
    struct timeval curr_time;
    int64_t  time_diff;
    static int64_t  fps = 0;
 
    sprites_to_screen(s->frames[s->counter], data);
    if (fps == 0)
    {
        fps = 1000000 / FPS;
        if (fps <= 0)
            fps = 500000;
    }
    gettimeofday(&curr_time, NULL);
    time_diff = (int64_t)(curr_time.tv_sec - data->last_frame_time.tv_sec) * 1000000L +
        (int64_t)(curr_time.tv_usec - data->last_frame_time.tv_usec);
    if (time_diff >= fps || s->counter == 0)
    {
        data->last_frame_time = curr_time;
        s->counter++; 
    }  
    if (s->counter >= s->size)
        s->counter = 0;
}

void    draw_sprites(t_data *data)
{
    if (data->flag_fire || data->flag_reload)
    {
        if (data->flag_fire)
        {
            sprites_handler(&data->fire, data);
            if (data->fire.counter == 0)
                data->flag_fire = 0;
        }
        else
        {
            sprites_handler(&data->reload, data);
            if (data->reload.counter == 0)
                data->flag_reload = 0;
        }
    }
    else
        sprites_handler(&data->normal, data);
}
