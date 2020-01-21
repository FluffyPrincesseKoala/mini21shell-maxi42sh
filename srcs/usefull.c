/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:54:50 by cylemair          #+#    #+#             */
/*   Updated: 2020/01/21 11:04:55 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		streplace(char **s1, char **s2)
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
	int		i;

	i = 0;
	while (array[i])
	{
		ft_putendl(array[i]);
		i++;
	}
}

int			count_delim(char *str, int delim)
{
	int		i;
	int		count;

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

char		*str_remove(char *str, char delim)
{
	char	*new;
	int		i;
	int		j;
	int		count;

	new = NULL;
	i = 0;
	j = 0;
	if (!(count = count_delim(str, delim)) && str)
		return (str);
	if (!(new = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] != delim)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}