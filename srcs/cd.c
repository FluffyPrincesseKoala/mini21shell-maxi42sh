/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:57:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/01/07 15:08:50 by cylemair         ###   ########.fr       */
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
			(*ell).env = change_key((*ell).env, new);
			(*ell).env = change_key((*ell).env, pwd);
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

void			tilt(t_vect **head, t_sh ell)
{
	t_vect		*lst;
	char		*map;
	char		**tab;
	int			i;

	if (head)
		lst = *head;
	while (lst)
	{
		i = -1;
		while (lst->arg[++i])
		{
			if (ft_strchr(lst->arg[i], '~'))
			{
				tab = ft_strsplit(lst->arg[i], '~');
				map = ft_strjoin(tab[0], findenv(ell.env, "HOME"));
				ft_strdel(&lst->arg[i]);
				lst->arg[i] = ft_strjoin(map, tab[0]);
				ft_strdel(&map);
				free_array(tab);
			}
		}
		lst = lst->next;
	}
}

int				get_var(t_vect **head, char **env)
{
	t_vect		*lst;
	char		*tmp;
	char		*var;
	int			i;
	int			count;

	count = 0;
	if (head)
		lst = *head;
	while (lst)
	{
		i = -1;
		while (lst->arg[++i])
		{
			if (lst->arg[i] && lst->arg[i][0] == '$')
			{
				var = ft_strdup(*((lst->arg + i) + 1));
				tmp = findenv(env, var);
				ft_strdel(&lst->arg[i]);
				ft_strdel(&var);
				lst->arg[i] = ft_strdup((tmp) ? tmp : "");
				count++;
			}
		}
		lst = lst->next;
	}
	return (count);
}
