/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chboegne <chboegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:10:38 by tcardair          #+#    #+#             */
/*   Updated: 2025/12/15 18:39:36 by chboegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_GC_H
# define MY_GC_H

# include "../libft.h"

# ifndef LIBFT_H
#  define LIBFT_H
#  include <unistd.h>

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *news);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
# endif

# ifndef S_LIST
#  define S_LIST

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
# endif

// MALLOC
void				*my_malloc(t_list **list_of_list, t_list **malloc_list,
						size_t size);
void				my_addtolist(t_list **list, void *data);
void				my_array_addtolist(t_list **list, void **data);

// CUSTOM FUNCTIONS
char				*my_strdup(t_list **malloc_list, char *src);
char				*my_strndup(t_list **malloc_list, char *str, int n);

// FREE
void				my_free_one(t_list **list, void *target);
void				my_free(t_list **list);
void				my_multi_free(t_list **list_of_list);

#endif