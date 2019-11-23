/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:36:56 by cylemair          #+#    #+#             */
/*   Updated: 2019/11/23 19:06:43 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        read_stdin(t_sh ell)
{
    int      res;
    char    *tmp;
    while (1)
    {
        ft_putstr(ell.prompt);
        get_next_line(0, &(ell.cmd));
        if (ft_strcmp(ell.cmd, ""))
        {
            ell.args = ft_strsplit(ell.cmd, ' ');
            if (!check_builtin(&ell))
            {
                ell.paths = ft_strsplit(findenv(ell.env, "PATH"), ':');
			    if ((tmp = build_path(ell)))
				    res = exec_cmd(ell, tmp);
		    	if (res || !tmp)
			    	ft_putendl_fd("Unknow command bro...", 2);
			    ft_strdel(&tmp);
            }
            ft_putchar('\n');
        }
		if (ell.cmd)
            ft_strdel(&(ell.cmd));
    }
}

int    check_builtin(t_sh *ell)
{
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
    return (0);
}