/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:18:38 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/20 19:18:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char		*build_path(t_sh ell, t_vect *lst)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**paths;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	paths = ft_strsplit(findenv(ell.env, "PATH"), ':');
	while (paths && paths[i])
	{
		tmp2 = ft_strjoin(paths[i], "/");
		tmp = (tmp2) ? ft_strjoin(tmp2, lst->arg[0]) : NULL;
		if (tmp && !access((const char*)tmp, X_OK))
        {
            ft_strdel(&tmp2);
            free_array(paths);
			return (tmp);
		}
        ft_strdel(&tmp);
        ft_strdel(&tmp2);
        i += 1;
	}
    ft_strdel(&tmp);
    ft_strdel(&tmp2);
    free_array(paths);
	return (NULL);
}

int			exec_cmd(t_sh ell, char *path, t_vect *cmd)
{
	int		status;
	pid_t	cpid;

	cpid = fork();
	if (cpid < 0)
	{
		ft_putstr_fd("fork faild at ", 2);
		ft_putnbr_fd((int)cpid, 2);
		ft_putchar('\n');
		exit(-1);
	}
	else if (cpid == 0)
	{
		if (execve(path, cmd->arg, ell.env) < 0)
			return (-1);
		else
        {
            if (ell.env)
                ft_putstr("env\n");
            if (ell.cmd)
                ft_putstr("cmd\n");
            if (ell.args)
                ft_putstr("args\n");
            if (ell.cmds)
                ft_putstr("cmds\n");
			exit(0);
        }
	}
	wait(&status);
	return ((status < 0) ? -1 : 0);
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
	fct[4].f = &builtin_echo;
	fct[4].name = "echo";
}

int			check_builtin(t_sh *ell, t_vect *cmd)
{
	t_built	fct[5];
	int		i;

	init(fct);
	i = 0;
	while (i != 5)
	{
		if (!ft_strcmp(cmd->arg[0], "exit"))
			return (-2);
		else if (!ft_strcmp(cmd->arg[0], fct[i].name))
		{
			fct[i].f(ell, cmd);
			return (1);
		}
		i++;
	}
	return (0);
}
