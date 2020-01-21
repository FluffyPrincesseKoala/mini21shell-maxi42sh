/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:18:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/01/09 17:34:50 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vect		*vect_new(char **arg)
{
	t_vect	*list;

	if (!(list = (t_vect*)malloc(sizeof(t_vect))))
		return (NULL);
	if (arg)
		list->arg = copy_array(arg);
	else
		list->arg = NULL;
	list->next = NULL;
	return (list);
}

t_vect		*vect_add(t_vect **head, t_vect *new)
{
	t_vect	*tmp;

	if (head)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*head);
}

void		free_vector(t_vect *head)
{
	if (head && head->next)
		free_vector(head->next);
	free_array(head->arg);
	free(head);
}
