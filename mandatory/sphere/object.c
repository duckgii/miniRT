/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeoshin <yeoshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:39:30 by yeoshin           #+#    #+#             */
/*   Updated: 2024/06/14 23:58:14 by yeoshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

t_object	*object(t_object_type type, void *element, t_color reflect)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (new == NULL)
		exit(1);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->reflect = reflect;
	return (new);
}

void	object_add(t_object **list, t_object *new)
{
	t_object	*cur;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = new;
}

t_object	*object_last(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}
