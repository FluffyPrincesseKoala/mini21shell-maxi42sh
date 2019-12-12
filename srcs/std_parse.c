/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:36:56 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/12 14:57:42 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	format_stdin(t_sh *ell)
{
	(*ell).args = ft_strsplit((*ell).cmd, ' ');
	get_var(&(*ell));
	tilt(&(*ell));
}

void		read_stdin(t_sh ell)
{
	int		built;
	char	*tmp;

	while (1 && built != -1)
	{
		ft_putstr(ell.prompt);
		get_next_line(0, &(ell.cmd));
		if (ft_strcmp(ell.cmd, ""))
		{
			format_stdin(&ell);
			if (!(built = check_builtin(&ell)) && built != -1)
			{
				ell.paths = ft_strsplit(findenv(ell.env, "PATH"), ':');
				if ((tmp = build_path(ell)))
					exec_cmd(ell, tmp);
				else if (!tmp)
					exec_cmd(ell, ell.args[0]);
				ft_strdel(&tmp);
			}
			free_array(ell.args);
		}
		if (ell.cmd)
			ft_strdel(&(ell.cmd));
	}
}

static void	init(t_built *fct)
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
