/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:51:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/04 19:53:08 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**change_key(char **env, char *var)
{
	int		key_len;
	int		i;
	int		j;
	char	**nenv;

	i = -1;
	j = -1;
	key_len = lendelim(var, '=', 0);
	if (!(nenv = (char**)malloc(sizeof(char *) * (array_len(env) + 1))))
		return (env);
	while (env[++i] && ++j)
	{
		if (key_len && !ft_strncmp(env[i], var, key_len))
			key_len = 0;
		nenv[j] = (!key_len) ? ft_strdup(var) : ft_strdup(env[i]);
	}
	nenv[j] = NULL;
	if (key_len)
	{
		free_array(nenv);
		return (addenv(env, var));
	}
	return (nenv);
}

char		**update_key(char **env, char *up, char *key, char *dest)
{
	char	*old;
	char	*tmp;
	char	*new;
	char	**tab;

	tab = NULL;
	if (up && key)
	{
		if (dest)
		{
			tmp = findenv(env, up);
			old = ft_strjoin(dest, tmp);
			tab = change_key(env, old);
		}
		new = ft_strjoin(up, key);
		env = change_key((tab) ? tab : env, new);
		free_array(tab);
		ft_strdel(&new);
		ft_strdel(&old);
	}
	return (env);
}
