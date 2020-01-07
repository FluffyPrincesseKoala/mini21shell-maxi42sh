/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:36:56 by cylemair          #+#    #+#             */
/*   Updated: 2020/01/07 15:25:53 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	format_stdin(t_sh *ell)
{
	char	**cmds;
	char	**args;
	int		i;

	i = 0;
	(*ell).cmds = NULL;
	cmds = ft_strsplit((*ell).cmd, ';');
	while (cmds[i])
	{
		args = ft_strsplit(cmds[i], ' ');
		if ((*ell).cmds)
			(*ell).cmds = vect_add(&(*ell).cmds, vect_new(args));
		else
			(*ell).cmds = vect_new(args);
		free_array(args);
		i++;
	}
	get_var(&(*ell).cmds, (*ell).env);
	tilt(&(*ell).cmds, *ell);
}

void		read_stdin(t_sh ell)
{
	int		built;
	t_vect	*lst;
	char	*tmp;

	built = 0;
	while (1 && built != -1)
	{
		ft_putstr(ell.prompt);
		get_next_line(0, &(ell.cmd));
		if (ft_strcmp(ell.cmd, ""))
		{
			format_stdin(&ell);
			lst = ell.cmds;
			while (lst)
			{
				if (!(built = check_builtin(&ell, lst)) && built != -1)
				{
					ell.paths = ft_strsplit(findenv(ell.env, "PATH"), ':');
					if ((tmp = build_path(ell)))
						exec_cmd(ell, tmp, lst);
					else if (!tmp)
						exec_cmd(ell, lst->arg[0], lst);
					ft_strdel(&tmp);
				}
				lst = lst->next;
			}
			free_vector(ell.cmds);
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

int			check_builtin(t_sh *ell, t_vect *cmd)
{
	t_built	fct[4];
	int		i;

	init(fct);
	i = 0;
	while (i != 4)
	{
		if (!ft_strcmp(cmd->arg[0], "exit"))
			return (-1);
		else if (!ft_strcmp(cmd->arg[0], fct[i].name))
		{
			fct[i].f(ell, cmd);
			return (1);
		}
		i++;
	}
	return (0);
}
