/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:16:50 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/22 12:17:15 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_vector	build_input_vectors(t_controls *dir)
{
	t_vector	input;
	double		len;

	input.dx = 0;
	input.dy = 0;
	if (dir->straight)
		input.dy += 1;
	if (dir->back)
		input.dy -= 1;
	if (dir->left)
		input.dx -= 1;
	if (dir->right)
		input.dx += 1;
	len = sqrt(input.dx * input.dx + input.dy * input.dy);
	if (len > 0)
	{
		input.dx /= len;
		input.dy /= len;
	}
	return (input);
}

bool	check_collision(t_data *data, t_vector *move)
{
	t_dpoint	curr_pos;

	curr_pos = data->p.pos;
	curr_pos.x += move->dx;
	curr_pos.y += move->dy;
	if (data->parse.map[(int)curr_pos.y][(int)curr_pos.x]
		!= '0' && data->parse.map[(int)curr_pos.y][(int)curr_pos.x] != 'O')
		return (false);
	return (true);
}

void	set_position(t_controls *dir, t_data *data)
{
	t_vector	input;
	t_vector	forward;
	t_vector	right;
	t_vector	move;

	input = build_input_vectors(dir);
	if (input.dx == 0 && input.dy == 0)
		return ;
	forward = data->p.v_dir;
	right.dx = -forward.dy;
	right.dy = forward.dx;
	move.dx = forward.dx * input.dy + right.dx * input.dx;
	move.dy = forward.dy * input.dy + right.dy * input.dx;
	move.dx *= WALK_SPEED;
	move.dy *= WALK_SPEED;
	if (check_collision(data, &move))
	{
		data->p.pos.x += move.dx;
		data->p.pos.y += move.dy;
	}
}
