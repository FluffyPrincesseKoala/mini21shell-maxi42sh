/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:52:17 by cylemair          #+#    #+#             */
/*   Updated: 2019/11/11 18:01:41 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		put_error(char *error, int exit)
(
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(RESET, 2);
	if (exit)
		exit(exit);
)

int         main(int argc, char **argv, char **env)
{
	t_sh	ell;
	char	*line;
	(void)argc;
	(void)argv;

	if (!(ell = malloc(sizeof(t_sh))))
		put_error("malloc failed alloc\n", -1);
	ell.prompt = ft_strdup("&> ");
	ell.env = copy_array(env);
	ell.real_env = env;
	while (1)
	{
		ft_putstr(prompt);
		get_next_line(0, &line);
		ft_putchar('\n');
		for (int i = 0; env[i]; i++)
			printf("%s\n", env[i]);
		ft_strdel(&line);
	}
}