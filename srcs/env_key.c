/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:51:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/18 15:02:16 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			lendelim(char *str, char delim, int start)
{
	int		i;

	i = start;
	while (str && str[i] && str[i] != delim)
		i++;
	return (i);
}

char		**change_key(char **env, char *var)
{
	int		key_len;
	int		i;
	int		j;
	char	**nenv;

	i = 0;
	j = 0;
	key_len = lendelim(var, '=', 0);
	if (!(nenv = (char**)malloc(sizeof(char *) * (array_len(env) + 1))))
		return (env);
	while (env[i])
	{
		if (key_len && !ft_strncmp(env[i], var, key_len))
		{
			key_len = 0;
			nenv[j] = ft_strdup(var);
		}
		else
			nenv[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	nenv[j] = NULL;
	return (!key_len ? nenv : addenv(env, var));
}

char		**update_key(char **env, char *up, char *key, char *dest)
{
	char	*old;
	char	*tmp;
	char	*new;
    char    **tab;

	if (up && key)
	{
		if (dest)
		{
			tmp = findenv(env, up);
			old = ft_strjoin(dest, tmp);
			tab = change_key(env, old);
		}
		new = ft_strjoin(up, key);
		env = change_key(env, new);
		ft_strdel(&new);
		ft_strdel(&old);
	}
	return (env);
}
