/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:53:40 by cylemair          #+#    #+#             */
/*   Updated: 2020/01/30 16:43:28 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env(t_sh *ell, t_vect *cmd)
{
	(void)cmd;
	putab((*ell).env);
}

void		builtin_unsetenv(t_sh *ell, t_vect *cmd)
{
	(*ell).env = delenv((*ell).env, cmd->arg[1]);
}

void		builtin_setenv(t_sh *ell, t_vect *cmd)
{
	char	*tmp;
	char	*tmpbis;
	int		i;

	i = 0;
	tmp = NULL;
	tmpbis = NULL;
	while (cmd->arg[i])
		i++;
	if (i == 2)
		tmp = ft_strdup(cmd->arg[1]);
	else if (i > 2)
	{
		tmp = ft_strjoin(cmd->arg[1], "=");
		tmpbis = ft_strjoin(tmp, cmd->arg[2]);
	}
	else
		return ;
	(*ell).env = change_key((*ell).env, tmpbis);
	ft_strdel(&tmp);
	ft_strdel(&tmpbis);
}

void		builtin_cd(t_sh *ell, t_vect *cmd)
{
	char	*tmp;
	char	*tmpbis;
	int		i;

	i = 0;
	tmp = NULL;
	tmpbis = NULL;
	while (cmd->arg[i])
		i++;
	if (i > 1 && !ft_strcmp(cmd->arg[1], "-"))
	{
		tmp = ft_strdup(findenv((*ell).env, "OLDPWD"));
		tmpbis = ft_strjoin("/", tmp);
		streplace((&cmd->arg[1]), &tmpbis);
	}
	else if (i == 1)
		cmd->arg[1] = ft_strdup(findenv((*ell).env, "HOME"));
	change_dir(cmd->arg[1], ell);
	ft_strdel(&tmp);
}

void		builtin_echo(t_sh *ell, t_vect *cmd)
{
	int		i;
	int		j;

	i = 0;
	(void)ell;
	while (cmd->arg[++i])
	{
		if (i >= 2)
			ft_putchar(' ');
		j = -1;
		while (cmd->arg[i][++j])
		{
			if ((cmd->arg[i][j] == '\\' || cmd->arg[i][j] == '\"'
				|| cmd->arg[i][j] == '\'') && cmd->arg[i][j - 1] == '\\')
				ft_putchar(cmd->arg[i][j]);
			else if (cmd->arg[i][j] != '\\' && cmd->arg[i][j] != '\"'
					&& cmd->arg[i][j] != '\'')
				ft_putchar(cmd->arg[i][j]);
		}
	}
	ft_putchar('\n');
}
