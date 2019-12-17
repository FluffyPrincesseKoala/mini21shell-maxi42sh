/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:52:17 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/17 14:21:32 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shlvlup(t_sh *ell)
{
	char	*old;
	char	*tmp;
	int		bis;

	old = ft_strdup(findenv((*ell).env, "SHLVL"));
	bis = ft_atoi(old);
	ft_strdel(&old);
	bis++;
	old = ft_strjoin((const char *)"SHLVL=", (tmp = ft_itoa(bis)));
	(*ell).env = delenv((*ell).env, "SHLVL");
	(*ell).env = addenv((*ell).env, old);
	ft_strdel(&old);
	ft_strdel(&tmp);
}

int         main(int argc, char **argv, char **env)
{
	t_sh	ell;
	(void)argc;
	(void)argv;

	ell.prompt = ft_strdup("&> ");
	// ell.env = copy_array(env);
	// ell.real_env = env;
	ell.env = env;
	ell.cmd = NULL;
	ell.paths = NULL;
	ell.args = NULL;
	shlvlup(&ell);
	read_stdin(ell);
	free(ell.prompt);
	free_array(ell.env);
	while (1);
	return (1);
}
