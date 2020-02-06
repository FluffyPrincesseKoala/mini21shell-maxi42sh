/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:54:50 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/06 16:14:39 by cylemair         ###   ########.fr       */
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

char        *replace_delim(char *str, char delim, char new)
{
    char    *ret;
    char    **tmp;
    int     i[3];

    i[1] = 0;
    i[0] = 0;
    tmp = ft_strsplit(str, delim);
    if (!(ret = malloc(sizeof(char) * (array_total_len(tmp) + array_len(tmp)))))
        return (NULL);
    while (tmp[i[0]])
    {
        i[2] = 0;
        while (tmp[i[0]][i[2]])
        {
            ret[i[1]] = tmp[i[0]][i[2]];
            i[1]++;
            i[2]++;
        }
        i[0]++;
        if (tmp[i[0]])
		{
		    ret[i[1]] = new;
			i[1]++;
		}
    }
    ret[i[1]] = '\0';
    free_array(tmp);
    return (ret);
}

// char        *replace_delim(char *str, char delim, char new)
// {
//     char    *ret;
//     char    **tmp;
//     int     i;

//     i = 0;
//     tmp = ft_strsplit(str, delim);
//     if (!(ret = malloc(sizeof(char) * (array_total_len(tmp) + array_len(tmp)))))
//         return (NULL);
//     while (tmp[i])
//     {
// 		printf("tmp[%d] [%s]\n", i, tmp[i]);
// 		if (tmp[i])
// 			ret = ft_strcat(ret, tmp[i]);
//         i++;
//         if (new && i <= array_len(tmp))
//             ret[ft_strlen(ret)] = new;
//     }
//     free_array(tmp);
// 	for (int l = 0 ; ret[l] ; l++) {
// 		printf("ret[%d] {%c}\n", l, ret[l]);
// 	}
//     return (ret);
// }