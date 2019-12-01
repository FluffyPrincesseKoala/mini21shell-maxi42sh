/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:18:38 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/01 17:23:37 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*build_path(t_sh ell)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (ell.paths[i])
	{
		tmp2 = ft_strjoin(ell.paths[i], "/");
		tmp = (tmp2) ? ft_strjoin(tmp2, ell.args[0]) : NULL;
		if (tmp && !access((const char*)tmp, X_OK))
			return (tmp);
		i += 1;
	}
	return (NULL);
}

int			exec_cmd(t_sh ell, char *path)
{
	int		status;
	pid_t	cpid;

	cpid = fork();
	signal(SIGINT, proc_signal_handler);
	if (cpid < 0)
	{
		ft_putstr_fd("fork faild at ", 2);
		ft_putnbr_fd((int)cpid, 2);
		ft_putchar('\n');
		exit(-1);
	}
	if (cpid == 0)
	{
		//printf("PATH = %s\n{", path);
		//for (int i = 0 ; ell.args[i] ; i++) {
		//	printf("\'%s\',\n", ell.args[i]);
		//}
		//printf("}\n");
		if (execve(path, ell.args, ell.env) == -1)
		{
			ft_putstr_fd("execve faild at ", 2);
			exit(-1);
		}
	}
	wait(&status);
	return (0);
}
