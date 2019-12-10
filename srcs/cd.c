/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:57:15 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/04 17:33:24 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    change_dir(const char *path, t_sh *ell)
{
	char	*pwd;
	char	*tmp;
	char	*new;
	char	*cwd;
	char	buff[4096 + 1];

	if (!access(path, F_OK))
	{
		if (chdir(path) == -1)
			puterror("Permission denied\n");
		else
		{
			if (!(cwd = getcwd(buff, 4096)))
				puterror("Permission denied\n");
			tmp = findenv((*ell).env, "PWD");
			pwd = ft_strjoin("OLDPWD=", tmp);
			new = ft_strjoin("PWD=", cwd);
			change_key((*ell).env, new);
			change_key((*ell).env, pwd);
			ft_strdel(&new);
			ft_strdel(&pwd);
		}
	}
	else
		puterror("No such file or directory\n");
}

int				is_dir(char *path)
{
	struct stat sb;

	if (lstat(path, &sb) == -1)
		puterror("lstat error\n");
	return (S_ISDIR(sb.st_mode));
}

int				is_file(char *path)
{
	struct stat sb;

	if (lstat(path, &sb) == -1)
		puterror("lstat error\n");
	return (S_ISREG(sb.st_mode));
}

int				tilt(t_sh *ell)
{
	char		*tmp;
	char		*map;
	char		**tab;
	int			i;

	i = 0;
	tmp = findenv((*ell).env, "HOME");
	while ((*ell).args[i])
	{
		if (ft_strchr((*ell).args[i], '~'))
		{
			tab = ft_strsplit((*ell).args[i], '~');
			map = ft_strjoin(tab[0], tmp);
			ft_strdel(&(*ell).args[i]);
			(*ell).args[i] = ft_strjoin(map, tab[0]);
			ft_strdel(&map);
			ft_strdel(&tab[0]);
			ft_strdel(&tab[1]);
			free(tab);
		}
		i++;
	}
	return (1);
}

int				get_var(t_sh *ell)
{
	char		*tmp;
	char		*var;
	int			i;
	int			count;

	i = 0;
	count = 0;
	while ((*ell).args[i])
	{
		if ((*ell).args[i][0] == '$')
		{
			var = ft_strdup(*((*ell).args + i) + 1);
			tmp = findenv((*ell).env, var);
			ft_strdel(&(*ell).args[i]);
			ft_strdel(&var);
			(*ell).args[i] = ft_strdup((tmp) ? tmp : "");
			count++;
		}
		i++;
	}
	return (count);
}
