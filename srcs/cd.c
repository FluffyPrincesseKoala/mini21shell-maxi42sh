/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:57:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/03 16:04:23 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_file(const char *path)
{
	struct stat sb;

	if (lstat(path, &sb) == -1)
		puterror("lstat error\n");
	return (S_ISREG(sb.st_mode));
}

void			change_dir(const char *path, t_sh *ell)
{
	char		*cwd;
	char		buff[4096 + 1];

	if (!access(path, F_OK))
	{
		if (chdir(path) == E_CHDIR)
			puterror(is_file(path) ? NODIR : DENY);
		else
		{
			if (!(cwd = getcwd(buff, 4096)))
				puterror("Permission denied\n");
			(*ell).env = update_key((*ell).env, "PWD=", cwd, "OLDPWD=");
		}
	}
	else
	{
		puterror((char*)path);
		puterror(": ");
		puterror("No such file or directory\n");
	}
}

void			tilt(t_vect **head, t_sh ell)
{
	t_vect		*lst;
	char		*map;
	char		**tab;
	int			i;

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
				tab = ft_strsplit(lst->arg[i], '~');
				map = ft_strjoin(tab[0], findenv(ell.env, "HOME="));
				ft_strdel(&lst->arg[i]);
				lst->arg[i] = ft_strjoin(map, tab[0]);
				ft_strdel(&map);
				free_array(tab);
			}
		}
		lst = lst->next;
	}
}

void			get_var(t_vect **head, char **env)
{
	t_vect		*lst;
	char		*tmp;
	char		*var;
	int			i;

	lst = NULL;
	if (head)
		lst = *head;
	while (lst)
	{
		i = -1;
		while (lst->arg[++i])
		{
			if (lst->arg[i] && lst->arg[i][0] == '$')
			{
                int k = 0;
                while (lst->arg[i][k] && lst->arg[i][k] != ':')
                    k++;
				var = ft_strndup(&lst->arg[i][1], k - 1);
				tmp = findenv(env, var);
                ft_strdel(&var);
                var = ft_strjoin(tmp, &lst->arg[i][k]);
				ft_strdel(&lst->arg[i]);
				lst->arg[i] = ft_strdup((var) ? var : "");
                ft_strdel(&var);
			}
		}
		lst = lst->next;
	}
}
