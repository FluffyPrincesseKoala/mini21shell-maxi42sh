/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:52:17 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/12 18:32:11 by cylemair         ###   ########.fr       */
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
    if (ell.env)
        array_len(ell.env);
    if (ell.args)
        array_len(ell.args);
    if (ell.cmds)
        free_vector(&ell.cmds);
    if (ell.prompt)
        ft_strdel(&ell.prompt);
	return (0);
}
