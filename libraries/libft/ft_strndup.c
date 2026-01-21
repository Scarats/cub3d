/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:31:55 by chboegne          #+#    #+#             */
/*   Updated: 2026/01/21 12:43:38 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, const int n)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (n + 1));
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
