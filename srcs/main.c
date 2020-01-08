/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:52:17 by cylemair          #+#    #+#             */
/*   Updated: 2020/01/08 18:10:13 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	shlvlup(t_sh *ell)
// {
// 	char	*old;
// 	char	*tmp;
// 	int		bis;

// 	old = findenv((*ell).env, "SHLVL");
// 	bis = ft_atoi(old);
// 	bis++;
// 	old = ft_strjoin((const char *)"SHLVL=", (tmp = ft_itoa(bis)));
// //	ft_strdel(&old);
// //	ft_strdel(&tmp);
// 	ft_putstr("WOLOLOLOOOW\n");

// }

int         main(int argc, char **argv, char **env)
{
	t_sh	ell;
	(void)argc;
	(void)argv;

	ell.prompt = ft_strdup("&> ");
	ell.env = env;
	//shlvlup(&ell);
	read_stdin(ell);
	return (1);
}
