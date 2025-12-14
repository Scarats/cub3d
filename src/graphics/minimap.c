#include "../cub3d.h"

void	draw_minimap(t_data *data, t_map map)
{
	printf("draw_minimap\n");
	(void)map;
	// TEMP ==================
	set_dir_from_pos(&data->direction_point, &data->position_point, data->direction_angle, data->win_width / 2);	
	// =======================
	draw_d_line(data->position_point, data->direction_point, P_WHITE, data->img_buff);
}