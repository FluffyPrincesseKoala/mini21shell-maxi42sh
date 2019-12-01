/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:36:56 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/01 17:40:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        read_stdin(t_sh ell)
{
	int      built;
	char    *tmp;

	while (1)
	{
		ft_putstr(ell.prompt);
		signal(SIGINT, signal_handler);
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
					ft_putendl_fd("Unknow command bro...", 2);
				if (tmp)
					ft_strdel(&tmp);
			}
			else if (built == -1)
				return ;
			for (int i = 0 ; ell.args[i] ; i++)
				ft_strdel(&ell.args[i]);
			ft_putchar('\n');
		}
		if (ell.cmd)
			ft_strdel(&(ell.cmd));
	}
}

int    check_builtin(t_sh *ell)
{
	if (!ft_strcmp((*ell).args[0], "exit"))
		return (-1);
	if (!ft_strcmp((*ell).args[0], "env"))
	{
		putab((*ell).env);
		return (1);
	}
	else if (!ft_strcmp((*ell).args[0], "unsetenv"))
	{
		(*ell).env = delenv((*ell).env, (*ell).args[1]);
		return (1);
	}
	else if (!ft_strcmp((*ell).args[0], "setenv"))
	{
		(*ell).env = change_key((*ell).env, (*ell).args[1]);
		return (1);
	}
	else if (!ft_strcmp((*ell).args[0], "cd"))
	{
		change_dir((*ell).args[1], ell);
		return (1);
	}
	return (0);
}