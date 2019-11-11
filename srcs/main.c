/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:52:17 by cylemair          #+#    #+#             */
/*   Updated: 2019/11/11 20:22:45 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		put_error(char *error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(RESET, 2);
}

int         main(int argc, char **argv, char **env)
{
	t_sh	ell;
	(void)argc;
	(void)argv;


	ell.prompt = ft_strdup("&> ");
	ell.env = copy_array(env);
	ell.real_env = env;
	while (1)
	{
		ft_putstr(ell.prompt);
		get_next_line(0, &(ell.cmd));
		ft_putchar('\n');
		ft_putstr(find_env(ell.env, ell.cmd));
		ft_putchar('\n');
		if (ell.cmd)
			ft_strdel(&(ell.cmd));
	}
}