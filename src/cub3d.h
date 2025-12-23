#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/libft/libft.h"
# include "../libraries/minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <string.h>

// COLORS
# define P_WHITE 0xFFFFFF
# define P_BLACK 0x000000
# define P_RED 0xFF0000
# define P_ORANGE 0xFFA500
# define P_GREEN 0x00FF00
# define P_BLUE 0x0000FF
# define P_LIGHT_BLUE 0xFFADD8E6
# define P_SUNSET 0xFFFFA500
# define P_BROWN 0x8B4513
# define P_PURPLE 0x800080
# define P_GREY 0xFF2E2E2E

// MACROS
# define SENSITIVITY 0.2 // From 0 to 1
# define POV 15          // Pixels shift per click
# define M_PI 3.14159265358979323846
# define FOV 0.99 // An angle
# define BORDER_THICKNESS 1 // In pixels
# define WALK_SPEED 0.1     // In blocks of the map per frame
# define MINI_MAP 0.2       // 0 to 1 surface d'occupation de la mini_map
// sprites
# define IMG_PS 4
# define TRANSPARENCY_THRESHOLD 130
# define PADDING 10	// To avoid the borders of the .xmp
# define MAGIC_NUMBER 6

// EVENT
typedef enum e_event
{
	EVENT_KEY_PRESSED = 2,
	EVENT_KEY_RELEASED = 3
}				t_event;

// KEYS
typedef enum e_key
{
	MOUSE = 6,
	KEY_ESC = 65307,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_UP = 65362,
	KEY_DOWN = 63364,
	KEY_W = 119,
	KEY_A = 97,
	KEY_D = 100,
	KEY_S = 115
}				t_key;

// PARSING
typedef struct s_parse
{
	char		*file;
	char		*stock;
	char		**element;
	char		**map;
	int			width;
	int			height;
	char		orientation;
}				t_parse;

typedef struct s_file
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
}				t_file;

typedef struct s_pex
{
	void		*img;
	int			*data;
	int			w;
	int			h;
	int			bpp;
	int			size;
	int			endian;
}				t_pex;

typedef struct s_tex
{
	t_pex		north;
	t_pex		south;
	t_pex		west;
	t_pex		east;
	int			floor;
	int			ceiling;
}				t_tex;

// MINI_MAP
typedef struct s_mini
{
	int			width;
	int			height;
	int			pixel;
}				t_mini;

typedef struct s_line
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			error;
}				t_line;

typedef struct s_vector
{
	double		dx;
	double		dy;
}				t_vector;

typedef struct s_dpoint
{
	double		x;
	double		y;
}				t_dpoint;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_controls
{
	// Direction
	bool		straight;
	bool		back;
	bool		left;
	bool		right;

	// POV
	bool		look_left;
	bool		look_right;
}				t_controls;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	
	// To store t_data
	void		*data;

	int			h;
	int			w;
}				t_img;

typedef struct s_sprite
{
	unsigned int size;
	unsigned int counter;
	t_pex **frames;

} t_sprite;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map;
}				t_map;

typedef struct s_player
{
	t_dpoint dir; // The point where the main vector hit a wall
	t_dpoint	pos;
	t_vector	v_plane;
	t_vector	v_dir;
	double		dir_angle;
}				t_player;

typedef struct s_dda
{
	t_point		map_pos;
	t_point		step;
	t_dpoint	delta_dist;
	t_dpoint	side_dist;
}				t_dda;

typedef struct s_data
{
	// CARLOS PARSER
	t_parse		parse;
	t_file		file;
	t_mini		mini;
	t_tex		tex;

	// MLX && WINDOW
	void		*mlx;
	void		*window;
	int			win_height;
	int			win_width;

	// IMAGES
	t_img *img_buff; // Image being created
	t_img *img_main; // Currently displayed
	// SPRITES
	t_sprite	normal;
	char		flag_fire;
	t_sprite	fire;
	char		flag_reload;
	t_sprite	reload;
	t_point		sprite_start;

	// FLAGS
	int			error;

	// PLAYER
	t_player	p;
	t_dda		dda;

	// t_dpoint	d_pos;
	t_controls	controls;

	// RAYCASTING
	t_dpoint	delta_dist;
	t_dpoint	side_dist;
	t_point		step;
	t_point		map_pos;

	// MINIMAP
	t_map		map;

	// MOUSE
	t_point		*last_mouse_pos;
	t_point		*curr_mouse_pos;

	// MALLOC
	t_list		*malloc_list;
}				t_data;

// MAIN
int				main_logic(t_data *data);

// UTILS
int				stop(t_data **data);
void			ft_init_struct(t_data *data, char *map);

// WINDOWS
void			create_window(t_data *data);
void			get_screen_dimentions(t_data *data);

// IMAGES
void			init_new_img(t_img *img, t_data *data);
void			reset_img(t_img *img);

// DRAW
void			my_pixel_put(t_img *img, int x, int y, int color);
void			draw_line(t_point a, t_point b, int color, t_img *img);
void			draw_d_line(t_dpoint a, t_dpoint b, int color, t_img *img);
int				get_offset(int y, int x, int line_length, int bits_per_pixel);

// HOOKS
void			set_hooks(t_data *data);

// RENDERING
void			render_img(t_img *img, t_data *data);
void			refresh_images(t_data *data);

// RAYCASTING
void			raycasting(t_data *data, t_player *p);

// SPRITES
void			get_sprites(t_data *data);

// POV
void			look_right(t_data *data);
void			stop_look_right(t_data *data);
void			look_left(t_data *data);
void			stop_look_left(t_data *data);
int				mouse_pov(int x, int y, t_data *data);
void			mouse_edge(t_data *data);

// DIRECTION
double			set_angle(double prev_angle, double pixel_pov_shift);
void			set_dir_from_pos(t_dpoint *direction, t_dpoint *position,
					double angle, double length);
t_vector		get_vector(double angle);
void			apply_pov(t_data *data);

// POSITION
void			go_straight(t_data *data, bool stop);
void			go_back(t_data *data, bool stop);
void			go_left(t_data *data, bool stop);
void			go_right(t_data *data, bool stop);
void			set_position(t_controls *dir, t_data *data);

// CARLOS PARSING
void			ft_draw_minimap(t_data *data);
// check_define.c
void			ft_map_size(t_data *data);
bool			ft_check_unclosed_map(char **map);
int				ft_nbr_and_player_orientation(t_data *data);
void			ft_isolate_map(t_data *data);
void			ft_convert_color(t_data *data);

// parsing.c
void			ft_parsing(t_data *data);
void			ft_draw_floor_and_celling(t_data *data);
void			ft_save_assets(t_data *data);

// MAIN
void			ft_error(t_data **data, const char *str, int code);
void			ft_free_str(char **str);
void			ft_free_arr(char ***arr);
void			ft_free_struct(t_data **data);
bool			ft_is_char_in_str(const char c, const char *type);

void    		sprites_handler(t_sprite *s, t_data *data);
#endif