#include "../cub3d.h"

void    sprites_to_screen(t_img *img, t_data *data)
{
    t_point p;

    p.x = 0;
    p.y = 0;
    
}

void    sprites_handler(t_sprite *s, t_data *data)
{


    if (s->counter >= s->size)
        s->counter = 0;
    else
        s->counter++; 
}

void    draw_sprites(t_data *data)
{
    if (data->flag_fire || data->flag_reload)
    {
        if (data->flag_fire)
        {
            sprites_handler(&data->fire, &data);
            if (data->fire.counter == 0)
                data->flag_fire = NULL;
        }
        else
        {
            sprites_handler(&data->reload, &data);
            if (data->reload.counter == 0)
                data->flag_reload = NULL;
        }
    }
    else
        sprites_to_screen(&data->normal, &data);
}
