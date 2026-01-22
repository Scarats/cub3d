/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:18:04 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/22 12:18:59 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Check if door is found in the block the player is looking at
void	handle_door(t_data *data)
{
	t_dpoint	block;
	double		check_dist;
	char		door;

	check_dist = DOOR_DISTANCE;
	block = data->p.pos;
	if (data->parse.map[(int)block.y][(int)block.x] == 'O')
		return ;
	block.x += data->p.v_dir.dx * check_dist;
	block.y += data->p.v_dir.dy * check_dist;
	door = data->parse.map[(int)block.y][(int)block.x];
	if (data->door)
		printf("door = %c\n", door);
	if (door == 'D' && data->door)
		data->parse.map[(int)block.y][(int)block.x] = 'O';
	else if (door == 'O' && data->door)
		data->parse.map[(int)block.y][(int)block.x] = 'D';
	data->door = false;
}

// If door is found AND the open door flag is set to true,
// then open/lock the door he looks at
