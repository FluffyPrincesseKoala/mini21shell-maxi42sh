/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:57:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/04 18:41:04 by cylemair         ###   ########.fr       */
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

static char		**split_var(char **env, char *str)
{
	char		*tmp;
	char		**var;
	int			k;

	k = 0;
	var = ft_strsplit(str, ':');
	while (var[k] && ft_strchr(var[k], '$'))
	{
		tmp = findenv(env, ft_strchr(var[k], '$') + 1);
		ft_strdel(&var[k]);
		var[k] = ft_strdup((tmp) ? tmp : "");
		k++;
	}
	var[k] = NULL;
	return (var);
}

static char		*use_shell_var(char **env, char *str)
{
	char		*tmp;
	char		*ret;
	char		**var;
	int			k;

	var = split_var(env, str);
	ret = NULL;
	k = array_len(var);
	while (k--)
	{
		tmp = ft_strjoin(var[k], ret);
		if (ret)
			ft_strdel(&ret);
		ret = ft_strdup(tmp);
		ft_strdel(&tmp);
		if (k)
		{
			tmp = ft_strjoin(":", ret);
			ft_strdel(&ret);
			ret = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
	free_array(var);
	return (ret);
}

void			get_var(t_vect **head, char **env)
{
	t_vect		*lst;
	char		*tmp;
	int			i;

	lst = NULL;
	if (head)
		lst = *head;
	while (lst)
	{
		i = -1;
		while (lst->arg[++i])
		{
			if (lst->arg[i] && ft_strchr(lst->arg[i], '$'))
			{
				tmp = use_shell_var(env, lst->arg[i]);
				ft_strdel(&lst->arg[i]);
				lst->arg[i] = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
		}
		lst = lst->next;
	}
}
