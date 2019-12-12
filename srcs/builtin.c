/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:53:40 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/12 14:57:35 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	    builtin_env(t_sh *ell)
{
	putab((*ell).env);
}

void	    builtin_unsetenv(t_sh *ell)
{
	(*ell).env = delenv((*ell).env, (*ell).args[1]);
}

void	    builtin_setenv(t_sh *ell)
{
	char	*tmp;
	char	*tmpbis;
	int		i;

	i = 0;
	tmp	= NULL;
	tmpbis	= NULL;
	while ((*ell).args[i])
		i++;
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

void	    builtin_cd(t_sh *ell)
{
	char	*tmp;
	int     i;

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

void    	builtin_echo(t_sh *ell)
{
	int	    i;

	i = 0;
	while ((*ell).args[++i])
	{
		ft_putstr((*ell).args[i]);
	}
	ft_putchar('\n');
}
