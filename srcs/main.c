/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:52:17 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/06 17:42:08 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char **argv, char **env)
{
	t_sh	ell;

	(void)argc;
	(void)argv;
	ell.cmd = NULL;
	ell.cmds = NULL;
	ell.args = NULL;
	ell.prompt = ft_strdup("\e[36m&> \033[0m");
	ell.env = env;
	read_stdin(ell);
	return (0);
}
