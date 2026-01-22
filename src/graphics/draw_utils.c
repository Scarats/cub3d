/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:20:07 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/22 12:20:21 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line_b(t_point *a, t_point *b, t_line *l)
{
	l->dx = abs(b->x - a->x);
	l->dy = abs(b->y - a->y);
	if (a->x < b->x)
		l->sx = 1;
	else
		l->sx = -1;
	if (a->y < b->y)
		l->sy = 1;
	else
		l->sy = -1;
	l->error = l->dx - l->dy;
}

void	draw_d_line_b(t_dpoint *a, t_dpoint *b, t_line *l)
{
	l->dx = fabs(b->x - a->x);
	l->dy = fabs(b->y - a->y);
	if (a->x < b->x)
		l->sx = 1;
	else
		l->sx = -1;
	if (a->y < b->y)
		l->sy = 1;
	else
		l->sy = -1;
	l->error = l->dx - l->dy;
}
