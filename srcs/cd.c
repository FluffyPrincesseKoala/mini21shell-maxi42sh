/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:57:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/01/30 16:59:38 by cylemair         ###   ########.fr       */
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

	printf("start\t[%s]\n", path);
	if (!access(path, F_OK))
	{
		printf("\033[1;31mpath ok\033[0m\n");
		if (chdir(path) == E_CHDIR)
		{
			printf("\033[1;31mchdir ok\033[0m\n");
			puterror(is_file(path) ? NODIR : DENY);
		}
		else
		{
			printf("\033[1;31melse ok\033[0m\n");
			if (!(cwd = getcwd(buff, 4096)))
				puterror("Permission denied\n");
			printf("\033[1;31mgetcwd ok\033[0m\n");
			(*ell).env = update_key((*ell).env, "PWD=", cwd, "OLDPWD=");
			printf("\033[1;31mpwd updated to %s\033[0m\n", findenv((*ell).env, "PWD"));
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
				var = ft_strdup(&lst->arg[i][1]);
				tmp = findenv(env, var);
				ft_strdel(&lst->arg[i]);
				ft_strdel(&var);
				lst->arg[i] = ft_strdup((tmp) ? tmp : "");
			}
		}
		lst = lst->next;
	}
}
