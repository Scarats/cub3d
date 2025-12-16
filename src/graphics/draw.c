#include "../cub3d.h"

// Mlx might add padding to the img addr for memory management purposes.
// Depending on the OS / Hardware.
// y * line_length to get to the right row (memory is just one long row)
// bits_per_pixel / 8 to converts bits to bytes
// so x * (bits_per_pixel / 8) to get to the right pixel.
int get_offset(int y, int x, int line_length, int bits_per_pixel)
{
	return (y * line_length + x * (bits_per_pixel / 8));
}

// Add a pixel to the given image and coordinates.
void my_pixel_put(t_img *img, int x, int y, int color)
{
	static t_data *data = NULL;
    char *dest;
	
	if (!img || !img->addr)
		return;
    if (!data)
        data = img->data;
    if (!(x >= 0 && x < data->win_width && y >= 0 && y < data->win_height))
		return;
    dest = img->addr + get_offset(y, x, img->line_length, img->bits_per_pixel);
    *(unsigned int *)dest = color;
}

void	draw_line(t_point a, t_point b, int color, t_img *img)
{
	t_line l;
	int e2;
	// int i = 0; // Just for testing

	l.dx = abs(b.x - a.x);
	l.dy = abs(b.y - a.y);
	if (a.x < b.x)
		l.sx = 1; 
	else
		l.sx = -1;
	if (a.y < b.y)
		l.sy = 1; 
	else
		l.sy = -1;
	
	l.error = l.dx - l.dy;	
	while(1)
	{
		my_pixel_put(img, a.x, a.y, color);

		if (a.x == b.x && a.y== b.y)
			break;
		e2 = 2 * l.error;	
		if (e2 > -l.dy)
		{
			l.error -= l.dy;
            a.x += l.sx;
        }
        if (e2 < l.dx)
        {
            l.error += l.dx;
            a.y += l.sy;
        }
	}
}

// Draw line with dpoint at minimap ratio
void	draw_d_line(t_dpoint a, t_dpoint b, int color, t_img *img)
{
	t_line l;
	int e2;

	l.dx = fabs(b.x - a.x);
	l.dy = fabs(b.y - a.y);
	if (a.x < b.x)
		l.sx = 1; 
	else
		l.sx = -1;
	if (a.y < b.y)
		l.sy = 1; 
	else
		l.sy = -1;
	
	l.error = l.dx - l.dy;	
	while(1)
	{
		my_pixel_put(img, a.x, a.y, color);

		if (a.x == b.x && a.y== b.y)
			break;
		e2 = 2 * l.error;	
		if (e2 > -l.dy)
		{
			l.error -= l.dy;
            a.x += l.sx;
        }
        if (e2 < l.dx)
        {
            l.error += l.dx;
            a.y += l.sy;
        }
	}
}


// AI ========================================================
static void	draw_point(t_img *img, int x, int y, int color, int radius)
{
	int dy;
	int dx;

	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			my_pixel_put(img, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

void draw_player(t_data *data)
{
    const double scale = 10.0;

    int px = (int)round(data->position.x * scale);
    int py = (int)round(data->position.y * scale);

    // draw a small point at player position (3x3 square)
    draw_point(data->img_buff, px, py, P_RED, 10);

    int len_px = 80; // length of the direction line in pixels

    int ex = px + (int)round(data->v_dir.dx * len_px);
    int ey = py + (int)round(data->v_dir.dy * len_px);

    draw_line((t_point){px, py}, (t_point){ex, ey}, P_WHITE, data->img_buff);
}