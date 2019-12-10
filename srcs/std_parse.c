/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:36:56 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/04 17:55:11 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        read_stdin(t_sh ell)
{
	int      built;
	char    *tmp;

	while (1)
	{
		ft_putchar('\n');
		//signal(SIGINT, signal_handler);
		ft_putstr(ell.prompt);
		get_next_line(0, &(ell.cmd));
		if (ft_strcmp(ell.cmd, ""))
		{
			ell.args = ft_strsplit(ell.cmd, ' ');
			get_var(&ell);
			tilt(&ell);
			if (!(built = check_builtin(&ell)) && built != -1)
			{
				ell.paths = ft_strsplit(findenv(ell.env, "PATH"), ':');
				if ((tmp = build_path(ell)))
					exec_cmd(ell, tmp);
				else if (!tmp)
					exec_cmd(ell, ell.args[0]);
				else
					puterror("commande inconnue...\n");
				if (tmp)
					ft_strdel(&tmp);
			}
			else if (built == -1)
				return ;
			for (int i = 0 ; ell.args[i] ; i++)
				ft_strdel(&ell.args[i]);
		}
		if (ell.cmd)
			ft_strdel(&(ell.cmd));
	}
}

void	builtin_env(t_sh *ell)
{
	putab((*ell).env);
}

void	builtin_unsetenv(t_sh *ell)
{
	(*ell).env = delenv((*ell).env, (*ell).args[1]);
}

void	builtin_setenv(t_sh *ell)
{
	char	*tmp;
	char	*tmpbis;
	int		i;

	i = 0;
	tmp	= NULL;
	tmpbis	= NULL;
	while ((*ell).args[i])
		i++;
	printf("%d\n", i);
	if (i == 2)
		tmp = ft_strdup((*ell).args[1]);
	else if (i > 2)
	{
		tmp = ft_strjoin((*ell).args[1], "=");
		tmpbis = ft_strjoin(tmp, (*ell).args[2]);
	}
	else
		return ;
	(*ell).env = change_key((*ell).env, tmpbis);
	ft_strdel(&tmp);
	ft_strdel(&tmpbis);
	if ((*ell).env)
		(*ell).real_env = (*ell).env;
}

void	streplace(char **s1, char **s2)
{
	ft_strdel(s1);
	*s1 = ft_strdup(*s2);
}

void	builtin_cd(t_sh *ell)
{
	char	*tmp;
	int i;

	i = 0;
	tmp = NULL;
	while ((*ell).args[i])
		i++;
	if (i > 1 && !ft_strcmp((*ell).args[1], "-"))
	{
		tmp = ft_strdup(findenv((*ell).env, "OLDPWD"));
		streplace((&(*ell).args[1]), &tmp);
	}
	else if (i == 1 && !(*ell).args[1])
		(*ell).args[1] = ft_strdup(findenv((*ell).env, "HOME"));
	change_dir((*ell).args[1], ell);
	ft_strdel(&tmp);
}

void	builtin_echo(t_sh *ell)
{
	int	i;

	i = 0;
	while ((*ell).args[++i])
	{
		ft_putstr((*ell).args[i]);
	}
	ft_putchar('\n');
}

void		init(t_built *fct)
{
	fct[0].f = &builtin_cd;
	fct[0].name = "cd";
	fct[1].f = &builtin_env;
	fct[1].name = "env";
	fct[2].f = &builtin_setenv;
	fct[2].name = "setenv";
	fct[3].f = &builtin_unsetenv;
	fct[3].name = "unsetenv";
}

int			check_builtin(t_sh *ell)
{
	t_built	fct[4];
	int		i;

	init(fct);
	i = 0;
	while (i != 4)
	{
		if (!ft_strcmp((*ell).args[0], "exit"))
			return (-1);
		else if (!ft_strcmp((*ell).args[0], fct[i].name))
		{
			fct[i].f(ell);
			return (1);
		}
		i++;
	}
	return (0);
}
