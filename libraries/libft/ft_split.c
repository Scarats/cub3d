/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcardair <tcardair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:46:48 by tcardair          #+#    #+#             */
/*   Updated: 2024/10/29 23:47:40 by tcardair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///////////////////////////////////////////////
// compte chaque mot separe par un caractere //
///////////////////////////////////////////////

static int	ft_count_word(const char *str, const char c)
{
	int	i;
	int	word;

	if (!str)
		return (0);
	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		word++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (word);
}

////////////////////////////////////////////////////////////////
// calcul la longueur d'une string depuis start jusqau'au cut //
////////////////////////////////////////////////////////////////

static int	ft_len_strt_stop(const char *str, int start, const char cut)
{
	int	stop;

	if (!str)
		return (0);
	while (str[start] && str[start] == cut)
		start++;
	stop = start;
	while (str[stop] && str[stop] != cut)
		stop++;
	return (stop - start);
}

////////////////////////////////////////////////////
// decoupe une string en array en fonction du cut //
////////////////////////////////////////////////////

char	**ft_split(const char *str, const char cut)
{
	int		i;
	int		j;
	int		word;
	int		start;
	char	**new;

	word = ft_count_word(str, cut);
	new = malloc(sizeof(char *) * (word + 1));
	if (!new || !str)
		return (NULL);
	i = 0;
	start = 0;
	while (i < word)
	{
		new[i] = malloc(sizeof(char) * (ft_len_strt_stop(str, start, cut) + 1));
		if (!new[i])
			return (NULL);
		j = 0;
		while (str[start] && str[start] == cut)
			start++;
		while (str[start] && str[start] != cut)
			new[i][j++] = str[start++];
		new[i++][j] = '\0';
	}
	return (new[i] = NULL, new);
}
