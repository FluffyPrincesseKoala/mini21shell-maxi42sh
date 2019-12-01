/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:52:17 by cylemair          #+#    #+#             */
/*   Updated: 2019/11/26 16:36:49 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		puterror(char *error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(RESET, 2);
}

void		putab(char **array)
{
	for (int i = 0 ; array[i] ; i++) {
		ft_putendl(array[i]);
	}
}

int			array_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void		free_tab(char ***tab)
{
	for (int i = 0 ; *tab[i] ; i++) {
		free(*tab[i]);
	}
	free(*tab);
}

int         main(int argc, char **argv, char **env)
{
	t_sh	ell;
	(void)argc;
	(void)argv;

	ell.prompt = ft_strdup("&> ");
	ell.env = copy_array(env);
	ell.real_env = env;
	read_stdin(ell);
	return (1);
}
