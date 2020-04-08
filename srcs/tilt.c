/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 19:05:04 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/06 19:08:15 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*nstrcat(char *dest, char *src, int start)
{
	int			i;

	i = 0;
	while (src[i])
	{
		dest[start] = src[i];
		start++;
		i++;
	}
	dest[start] = '\0';
	return (dest);
}

static char		*replace_tilt(char *str, char *new, size_t len)
{
	char		*ret;
	int			j;
	int			k;

	j = -1;
	k = 0;
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (str[++j])
	{
		if (str[j] != '~')
		{
			ret[k] = str[j];
			k++;
		}
		else
		{
			ret = nstrcat(ret, new, k);
			k += ft_strlen(new);
		}
	}
	ret[k] = '\0';
	return (ret);
}

static char		*find_tilt(char *str, char **env)
{
	size_t		len;
	size_t		diff;
	char		*tmp;
	char		*ret;

	tmp = ft_strdup(findenv(env, "HOME="));
	diff = count_delim(str, '~') * ft_strlen(tmp);
	len = ft_strlen(str) + diff - count_delim(str, '~');
	ret = replace_tilt(str, tmp, len);
	ft_strdel(&tmp);
	return (ret);
}

void			tilt(t_vect **head, t_sh ell)
{
	t_vect		*lst;
	char		*map;
	int			i;

	map = NULL;
	lst = NULL;
	if (head)
		lst = *head;
	while (lst)
	{
		i = -1;
		while (lst->arg[++i])
		{
			if (ft_strchr(lst->arg[i], '~'))
			{
				map = find_tilt(lst->arg[i], ell.env);
				ft_strdel(&lst->arg[i]);
				lst->arg[i] = ft_strdup(map);
				ft_strdel(&map);
			}
		}
		lst = lst->next;
	}
}
