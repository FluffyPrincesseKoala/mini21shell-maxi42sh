/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:54:50 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/12 13:59:39 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	    streplace(char **s1, char **s2)
{
	ft_strdel(s1);
	*s1 = ft_strdup(*s2);
}

void		free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		ft_strdel(&array[i]);
		i++;
	}
	free(array);
}

int			array_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void		puterror(char *error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(RESET, 2);
}

void		putab(char **array)
{
	for (int i = 0 ; array[i] ; i++) {
		ft_putendl(array[i]);
	}
}
