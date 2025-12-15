/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:39:37 by chboegne          #+#    #+#             */
/*   Updated: 2025/12/15 18:37:51 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_str(char **str)
{
	if (!*str)
		return ;
	free(*str);
	*str = NULL;
}

void	ft_free_arr(char ***arr)
{
	int	i;

	if (!*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		ft_free_str(&(*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	ft_free_struct(t_data **s)
{
	ft_free_str(&(*s)->parse.stock);
	ft_free_arr(&(*s)->parse.element);
	ft_free_arr(&(*s)->parse.map);
	ft_free_str(&(*s)->file.north);
	ft_free_str(&(*s)->file.south);
	ft_free_str(&(*s)->file.west);
	ft_free_str(&(*s)->file.east);
	ft_free_str(&(*s)->file.floor);
	ft_free_str(&(*s)->file.ceiling);
	free(*s);
	*s = NULL;
}

static void	ft_init_struct(t_data *s, char *map)
{
	s->parse.file = map;
	s->parse.stock = NULL;
	s->parse.element = NULL;
	s->parse.element = ft_split("NO-SO-WE-EA-F-C", '-');
	if (!s->parse.element)
		ft_error(&s, "💥 S->PARSE.ELEMENTS FT_INIT_STRUCT 💥", 1);
	s->parse.map = NULL;
	s->file.north = NULL;
	s->file.south = NULL;
	s->file.west = NULL;
	s->file.east = NULL;
	s->file.floor = NULL;
	s->file.ceiling = NULL;
}
