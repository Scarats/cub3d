#ifndef CUB3D_H
#define CUB3D_H

#include "./libraries/libft/libft.h"
#include "./libraries/minilibx-linux/mlx.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>

// COLORS
#define P_WHITE	  0xFFFFFF
#define P_BLACK	  0x000000
#define P_RED     0xFF0000
#define P_ORANGE  0xFFA500
#define P_GREEN   0x00FF00
#define P_BLUE    0x0000FF
#define P_BROWN   0x8B4513
#define P_PURPLE  0x800080
#define P_RESET   0x000000

// CONTROLS
#define SENSITIVITY 0.2
#define POV	10 // Pixels shift per click
#define M_PI 3.14159265358979323846
#define FOV	66

typedef enum e_event
{
	EVENT_KEY_PRESSED = 2,
	EVENT_KEY_RELEASED = 3
} t_event;

typedef enum e_key
{
	MOUSE = 6,
	KEY_ESC = 65307,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_UP = 65362,
	KEY_DOWN = 63364,
} t_key;

 typedef struct s_line
 {
	int dx;
	int dy;
	int sx;
	int sy;
	int error;
} t_line;

typedef struct s_vector
{
	double	dx;
	double	dy;
}	t_vector;

typedef struct s_dpoint
{
	double	x;	// Width
	double	y;	// Height
}	t_dpoint;

typedef struct s_point
{
	int x;	// Width
	int y;	// Height
}	t_point;

typedef struct s_controls
{
	// Direction
	bool up;
	bool down;
	bool left;
	bool right;
	// POV
	bool look_left;
	bool look_right;
} t_controls;

typedef struct s_img
{
	void *mlx_img;
	char *addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	void *data;
}	t_img;

typedef struct s_data
{
	// MLX && WINDOW
	void *mlx;
	void *window;
	int win_height;
	int win_width;

	// IMAGES
	t_img *img_buff;	// Image being created
	t_img *img_main;	// Currently displayed

	// FLAGS
	int error;

	// PLAYER
	// t_point		direction; // Just for testing
	t_vector	direction;
	t_dpoint	position;
	double		direction_angle;
	t_controls	controls; 

	// RAYCASTING
	t_dpoint	delta_dist;
	t_dpoint	side_dist;
	t_point		step;
	t_point		map_pos;

	// MOUSE
	t_point *last_mouse_pos;
	t_point *curr_mouse_pos;

	// MALLOC
	t_list *malloc_list;
} t_data;

// MAIN
int		main_logic(t_data *data);

// UTILS
int stop(t_data *data);

// WINDOWS
void create_window(t_data *data);
int close_window(int keycode, t_data *data);

// IMAGES
void	init_new_img(t_img *img, t_data *data);
void	reset_img(t_img *img);

// DRAW
void my_pixel_put(t_img *img, int x, int y, int color);
void	draw_line(t_point a, t_point b, int color, t_img *img);
int get_offset(int y, int x, int line_length, int bits_per_pixel);

// HOOKS
void	set_hooks(t_data *data);

// RENDERING
void	render_img(t_img *img, t_data *data);
void	refresh_images(t_data *data);

// RAYCASTING

// ANGLE
void	get_direction(t_data *data, double pixel_pov_shift);
void	key_direction();

// POV
void	look_right(t_data *data);
void	stop_look_right(t_data *data);
void	look_left(t_data *data);
void	stop_look_left(t_data *data);
int		mouse_pov(int x, int y, t_data *data);
void    mouse_edge(t_data *data);

// DIRECTION
double	set_angle(double prev_angle, double	pixel_pov_shift);
void    set_dir_from_pos(t_point *direction, t_point *position, double angle, double length);
// t_vector	get_vector(t_point position, double angle);

// POSITION
void	get_position(t_data *data);

// MINIMAP
void	print_direction(t_data *data);

#endif