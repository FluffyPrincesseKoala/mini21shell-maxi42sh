/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:22:37 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/21 21:39:29 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			array_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int			array_total_len(char **array)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (array[i])
	{
		len += ft_strlen(array[i]);
		i++;
	}
	return (len);
}

size_t		count_lst(t_vect *head)
{
	t_vect	*lst;
	size_t	count;

	count = 0;
	lst = head;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

size_t		count_delim(char *str, int delim)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == delim)
			count++;
		i++;
	}
	return (count);
}

void		free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		////printf("array[%d] {%p}\n", i, array[i]);
	    ft_strdel(&array[i]);
		i++;
	}
	//printf("array {%p}\n", array);
	free(array);
	array = NULL;
}
