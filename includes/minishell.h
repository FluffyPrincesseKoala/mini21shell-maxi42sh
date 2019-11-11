/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:36:43 by cylemair          #+#    #+#             */
/*   Updated: 2019/11/11 17:11:30 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include "../libft/get_next_line.h"
# include "../libft/libft.h"

# define RED 	"\033[1;31m"
# define RESET	"\033[0m"

typedef struct  s_sh
{
	char		**env;

	// useless = priceless
	char		*prompt;
	// debug
	char		**real_env;
}				t_sh;

char        **copy_array(char **array);

#endif