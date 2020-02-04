/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:54:50 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/04 16:20:58 by cylemair         ###   ########.fr       */
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

char		*str_remove(char *str, char delim)
{
	char	*new;
	int		i;
	int		j;
	size_t	count;

	new = NULL;
	i = 0;
	j = 0;
	if (!(count = count_delim(str, delim)))
		return (NULL);
	if (!(new = malloc(sizeof(char) * ((ft_strlen(str) - count) + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] != delim)
		{
			new[j] = str[i];
			j++;
		}
        if ((count = count_delim(&str[i], delim)))
        {
            while (str[i] == delim && str[i])
        		i++;
            if (str[i] && new[j])
            {
                new[j] = ' ';
                j++;
            }
        }
        i++;
	}
	new[j] = '\0';
    ft_putstr(new);
	return (new);
}


int  array_total_len(char **array)
{
    int     i;
    int     len;

    i = 0;
    len = 0;
    while (array[i])
    {
        len += ft_strlen(array[i]);
        i++;
    }
    return (len);
}

char        *replace_delim(char *str, char delim, char new)
{
    char    *ret;
    char    **tmp;
    int     i;
    int     j;
    int     k;

    j = 0;
    i = 0;
    tmp = ft_strsplit(str, delim);
    while (tmp[i])
        i++;
    if (!(ret = malloc(sizeof(char) * (array_total_len(tmp) + i))))
        return (NULL);
    i = 0;
    while (tmp[i])
    {
        k = 0;
        while (tmp[i][k])
        {
            ret[j] = tmp[i][k];
            j++;
            k++;
        }
        i++;
        if (tmp[i])
        {
            ret[j] = new;
            j++;
        }
    }
    ret[j] = '\0';
    free_array(tmp);
    return (ret);
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
