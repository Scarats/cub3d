/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:02 by tcardair          #+#    #+#             */
/*   Updated: 2025/12/15 18:35:42 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_gc.h"

// strdup and add the allocated memory to the list.
char	*my_strdup(t_list **malloc_list, char *src)
{
	char	*dup;

	if (!src || !malloc_list)
		return (NULL);
	dup = ft_strdup(src);
	if (!dup)
		return (NULL);
	my_addtolist(malloc_list, dup);
	return (dup);
}

char	*my_strndup(t_list **malloc_list, char *str, int n)
{
	int		i;
	char	*new;

	if (!malloc_list || !str)
		return (NULL);
	new = my_malloc(NULL, malloc_list, sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
