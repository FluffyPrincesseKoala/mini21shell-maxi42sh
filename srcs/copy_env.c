/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:58:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/03 16:52:40 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**copy_array(char **array)
{
	char	**new;
	int		i;

	i = 0;
	while (array[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char		*findenv(char **env, char *var)
{
	int		i;
    int     len;

	i = 0;
    len = lendelim(var, '=', 0);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var, len))
			return (*(env + i) + len + 1);
		i += 1;
	}
	return (NULL);
}

char		**delenv(char **env, char *var)
{
	char	**new;
	int		i;
	int		j;
	int		check;

	i = 0;
	j = 0;
	check = 0;
	if (!(new = malloc(sizeof(char*) * (array_len(env)))))
		return (NULL);
	while (env[i])
	{
		if (check || ft_strncmp(env[i], var, ft_strlen(var)))
		{
			new[j] = ft_strdup(env[i]);
			j++;
		}
		else
			check = 1;
		i++;
	}
    printf("j = %d i = %d\n", j, i);
	if (!check)
    {
        while (j--)
            ft_strdel(&new[j]);
	    return (env);
    }
    new[j] = NULL;
    return (new);
}

char		**addenv(char **env, char *var)
{
	char	**new;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	i++;
	new[i] = NULL;
	//printf("ADDENV\tnew {%p} | *new{%p}\n", new, *new);
	return (new);
}
