#include "../cub3d.h"

// Compute the ray direction according to x (position on the screen) and the curr direction
void	compute_ray_direction(t_player *p, int x, int width, t_vector *ray_dir)
{
	double	screen_x;

	screen_x = 2.0 * x / width - 1.0;
	ray_dir->dx = p->v_dir.dx + p->v_plane.dx * screen_x;
	ray_dir->dy = p->v_dir.dy + p->v_plane.dy * screen_x;
}

void	init_dda(t_dda *dda, t_player *p, t_vector *ray_dir)
{
	dda->map_pos.x = (int)p->pos.x;
	dda->map_pos.y = (int)p->pos.y;
	dda->delta_dist.x = fabs(1.0 / ray_dir->dx);
	dda->delta_dist.y = fabs(1.0 / ray_dir->dy);
	if (ray_dir->dx < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (p->pos.x - dda->map_pos.x) * dda->delta_dist.x;
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = (dda->map_pos.x + 1.0 - p->pos.x)
			* dda->delta_dist.x;
	}
	if (ray_dir->dy < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (p->pos.y - dda->map_pos.y) * dda->delta_dist.y;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = (dda->map_pos.y + 1.0 - p->pos.y)
			* dda->delta_dist.y;
	}
}

void	dda_wall_detection(t_dda *dda, t_data *data, int *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->map_pos.x += dda->step.x;
			*side = 0;
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->map_pos.y += dda->step.y;
			*side = 1;
		}
		if (dda->map_pos.y < 0 || dda->map_pos.y >= data->parse.height
			|| dda->map_pos.x < 0 || dda->map_pos.x >= data->parse.width)
			break ;
		if (data->parse.map[dda->map_pos.y][dda->map_pos.x] != '0')
			hit = 1;
	}
}

void	compute_hit_point(t_player *player, t_dda *dda, int side,
		t_dpoint *hit_point, t_vector *ray_dir)
{
	double	distance;

	if (side == 0)
		distance = dda->side_dist.x - dda->delta_dist.x;
	else
		distance = dda->side_dist.y - dda->delta_dist.y;
	hit_point->x = player->pos.x + ray_dir->dx * distance;
	hit_point->y = player->pos.y + ray_dir->dy * distance;
}

double	get_distance(int side, t_dda *dda)
{
	if (side == 0)
		return (dda->side_dist.x - dda->delta_dist.x);
	else
		return (dda->side_dist.y - dda->delta_dist.y);
}

// void	draw_wall(int x, double distance, t_data *data, int side)
// {
// 	int			line_height;
// 	int			draw_start;
// 	int			draw_end;
// 	static int	height = -1;

// 	if (height == -1)
// 		height = data->win_height;
// 	line_height = (int)(height / distance);
// 	draw_start = -line_height / 2 + height / 2;
// 	draw_end = line_height / 2 + height / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	if (draw_end >= height)
// 		draw_end = height - 1;
// 	while (draw_start <= draw_end)
// 	{
// 		if (side == 0 && data->dda.step.x == -1)
// 			my_pixel_put(data->img_buff, x, draw_start, P_PURPLE);
// 		else if (side == 0)
// 			my_pixel_put(data->img_buff, x, draw_start, P_BLUE);
// 		else if (data->dda.step.y == -1)
// 			my_pixel_put(data->img_buff, x, draw_start, P_WHITE);
// 		else
// 			my_pixel_put(data->img_buff, x, draw_start, P_ORANGE);
// 		draw_start++;
// 	}
// }

// void	draw_wall(int x, double distance, t_data *data, int side)
// {
// 	int				line_height;
// 	int				draw_start;
// 	int				draw_end;
// 	static int		height = -1;
// 	int				tex_x;
// 	int				tex_y;
// 	int				d;
// 	unsigned int	color;
// 	double			wall_x;
// 	int				current_y;
// 	int				pixel_offset;

// 	// Initialiser la hauteur une seule fois
// 	if (height == -1)
// 		height = data->win_height;
// 	// Calculer la hauteur de la ligne et les limites de dessin
// 	line_height = (int)(height / distance);
// 	draw_start = -line_height / 2 + height / 2;
// 	draw_end = line_height / 2 + height / 2;
// 	// Corriger les limites si nécessaire
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	if (draw_end >= height)
// 		draw_end = height - 1;
// 	// Calculer la position horizontale dans la texture
// 	// Utiliser toujours la même image (data->image)
// 	if (side == 0)
// 		wall_x = data->p.pos.y + distance * data->p.v_dir.dy;
// 	else
// 		wall_x = data->p.pos.x + distance * data->p.v_dir.dx;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * (double)data->tex.north.w);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= data->tex.north.w)
// 		tex_x = data->tex.north.w - 1;
// 	// Initialiser la position verticale actuelle
// 	current_y = draw_start;
// 	// Dessiner chaque pixel de la colonne
// 	while (current_y <= draw_end)
// 	{
// 		// Calculer la position verticale dans la texture
// 		d = current_y * 256 - height * 128 + line_height * 128;
// 		tex_y = ((d * data->tex.north.h) / line_height) / 256;
// 		if (tex_y < 0)
// 			tex_y = 0;
// 		if (tex_y >= data->tex.north.h)
// 			tex_y = data->tex.north.h - 1;
// 		// Récupérer la couleur du pixel dans la texture
// 		pixel_offset = get_offset(tex_y, tex_x, data->tex.north.size,
// 				data->tex.north.bpp);
// 		color = *(unsigned int *)(data->tex.north.img + pixel_offset);
// 		// Dessiner le pixel
// 		my_pixel_put(data->img_buff, x, current_y, color);
// 		current_y++;
// 	}
// }

// void	draw_wall(int x, double distance, t_data *data, int side)
// {
// 	int				line_height;
// 	int				draw_start;
// 	int				draw_end;
// 	static int		height = -1;
// 	int				tex_x;
// 	int				tex_y;
// 	int				d;
// 	unsigned int	color;
// 	double			wall_x;
// 	int				current_y;
// 	int				pixel_offset;

// 	// Initialiser la hauteur une seule fois
// 	if (height == -1)
// 		height = data->win_height;
// 	// Calculer la hauteur de la ligne et les limites de dessin
// 	line_height = (int)(height / distance);
// 	draw_start = -line_height / 2 + height / 2;
// 	draw_end = line_height / 2 + height / 2;
// 	// Corriger les limites si nécessaire
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	if (draw_end >= height)
// 		draw_end = height - 1;
// 	// Calculer la position horizontale dans la texture
// 	if (side == 0)
// 		wall_x = data->p.pos.y + distance * data->p.v_dir.dy;
// 	else
// 		wall_x = data->p.pos.x + distance * data->p.v_dir.dx;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * (double)data->tex.north.w);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= data->tex.north.w)
// 		tex_x = data->tex.north.w - 1;
// 	// Dessiner chaque pixel de la colonne
// 	current_y = draw_start;
// 	while (current_y <= draw_end)
// 	{
// 		// Calculer la position verticale dans la texture
// 		d = current_y * 256 - height * 128 + line_height * 128;
// 		tex_y = ((d * data->tex.north.h) / line_height) / 256;
// 		if (tex_y < 0)
// 			tex_y = 0;
// 		if (tex_y >= data->tex.north.h)
// 			tex_y = data->tex.north.h - 1;
// 		// Calculer l'offset du pixel dans la texture
// 		pixel_offset = tex_y * (data->tex.north.size / 4) + tex_x;
// 		// Simplifié pour 32 bits (ARGB)
// 		// Lire la couleur directement depuis data->tex.north.data
// 		color = data->tex.north.data[pixel_offset];
// 		// Dessiner le pixel
// 		my_pixel_put(data->img_buff, x, current_y, color);
// 		current_y++;
// 	}
// }

// void	raycasting(t_data *data, t_player *p)
// {
// 	int			x;
// 	int			side;
// 	t_vector	ray_dir;
// 	double		distance;

// 	x = -1;
// 	while (++x < data->win_width)
// 	{
// 		compute_ray_direction(p, x, data->win_width, &ray_dir);
// 		init_dda(&data->dda, p, &ray_dir);
// 		dda_wall_detection(&data->dda, data, &side);
// 		distance = get_distance(side, &data->dda);
// 		draw_wall(x, distance, data, side);
// 	}
// }

// void	draw_wall(int x, double distance, t_data *data, int side,
// 		int orientation)
// {
// 	int				line_height;
// 	int				draw_start;
// 	int				draw_end;
// 	static int		height = -1;
// 	int				tex_x;
// 	int				tex_y;
// 	int				d;
// 	unsigned int	color;
// 	double			wall_x;
// 	int				current_y;
// 	int				pixel_offset;
// 	t_pex			*current_tex;

// 	// Initialiser la hauteur une seule fois
// 	if (height == -1)
// 		height = data->win_height;
// 	// Calculer la hauteur de la ligne et les limites de dessin
// 	line_height = (int)(height / distance);
// 	draw_start = -line_height / 2 + height / 2;
// 	draw_end = line_height / 2 + height / 2;
// 	// Corriger les limites si nécessaire
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	if (draw_end >= height)
// 		draw_end = height - 1;
// 	// Choisir la texture en fonction de l'orientation
// 	if (orientation == 0) // Nord
// 		current_tex = &data->tex.north;
// 	else if (orientation == 1) // Sud
// 		current_tex = &data->tex.south;
// 	else if (orientation == 2) // Ouest
// 		current_tex = &data->tex.west;
// 	else // Est
// 		current_tex = &data->tex.east;
// 	// Calculer la position horizontale dans la texture
// 	if (side == 0)
// 		wall_x = data->p.pos.y + distance * data->p.v_dir.dy;
// 	else
// 		wall_x = data->p.pos.x + distance * data->p.v_dir.dx;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * (double)current_tex->w);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= current_tex->w)
// 		tex_x = current_tex->w - 1;
// 	// Dessiner chaque pixel de la colonne
// 	current_y = draw_start;
// 	while (current_y <= draw_end)
// 	{
// 		// Calculer la position verticale dans la texture
// 		d = current_y * 256 - height * 128 + line_height * 128;
// 		tex_y = ((d * current_tex->h) / line_height) / 256;
// 		if (tex_y < 0)
// 			tex_y = 0;
// 		if (tex_y >= current_tex->h)
// 			tex_y = current_tex->h - 1;
// 		// Calculer l'offset du pixel dans la texture
// 		pixel_offset = tex_y * (current_tex->size / 4) + tex_x;
// 		// Lire la couleur directement depuis current_tex->data
// 		color = current_tex->data[pixel_offset];
// 		// Dessiner le pixel
// 		my_pixel_put(data->img_buff, x, current_y, color);
// 		current_y++;
// 	}
// }

void	draw_wall(int x, double distance, t_data *data, int side,
		int orientation, t_vector ray_dir)
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	static int		height = -1;
	int				tex_x;
	int				tex_y;
	int				d;
	unsigned int	color;
	double			wall_x;
	int				current_y;
	int				pixel_offset;
	t_pex			*current_tex;

	// Initialiser la hauteur une seule fois
	if (height == -1)
		height = data->win_height;
	// Calculer la hauteur de la ligne et les limites de dessin
	line_height = (int)(height / distance);
	draw_start = -line_height / 2 + height / 2;
	draw_end = line_height / 2 + height / 2;
	// Corriger les limites si nécessaire
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= height)
		draw_end = height - 1;
	// Choisir la texture en fonction de l'orientation
	if (orientation == 0) // Nord
		current_tex = &data->tex.north;
	else if (orientation == 1) // Sud
		current_tex = &data->tex.south;
	else if (orientation == 2) // Ouest
		current_tex = &data->tex.west;
	else // Est
		current_tex = &data->tex.east;
	// Calculer la position horizontale dans la texture
	if (side == 0) // Mur vertical (est/ouest)
		wall_x = data->p.pos.y + distance * ray_dir.dy;
	else // Mur horizontal (nord/sud)
		wall_x = data->p.pos.x + distance * ray_dir.dx;
	wall_x -= floor(wall_x); // Garder uniquement la partie fractionnaire
	tex_x = (int)(wall_x * (double)current_tex->w);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= current_tex->w)
		tex_x = current_tex->w - 1;
	// Dessiner chaque pixel de la colonne
	current_y = draw_start;
	while (current_y <= draw_end)
	{
		// Calculer la position verticale dans la texture
		d = current_y * 256 - height * 128 + line_height * 128;
		tex_y = ((d * current_tex->h) / line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= current_tex->h)
			tex_y = current_tex->h - 1;
		// Calculer l'offset du pixel dans la texture
		pixel_offset = tex_y * (current_tex->size / 4) + tex_x;
		// Lire la couleur directement depuis current_tex->data
		color = current_tex->data[pixel_offset];
		// Dessiner le pixel
		my_pixel_put(data->img_buff, x, current_y, color);
		current_y++;
	}
}

void	raycasting(t_data *data, t_player *p)
{
	int			x;
	int			side;
	t_vector	ray_dir;
	double		distance;

	int orientation; // 0: nord, 1: sud, 2: ouest, 3: est
	x = -1;
	while (++x < data->win_width)
	{
		compute_ray_direction(p, x, data->win_width, &ray_dir);
		init_dda(&data->dda, p, &ray_dir);
		dda_wall_detection(&data->dda, data, &side);
		// Déterminer l'orientation du mur
		if (side == 0) // Mur vertical (nord/sud)
		{
			if (ray_dir.dx > 0)
				orientation = 3; // Est
			else
				orientation = 2; // Ouest
		}
		else // Mur horizontal (nord/sud)
		{
			if (ray_dir.dy > 0)
				orientation = 1; // Sud
			else
				orientation = 0; // Nord
		}
		distance = get_distance(side, &data->dda);
		draw_wall(x, distance, data, side, orientation, ray_dir);
	}
}
