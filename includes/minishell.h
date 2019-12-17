/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:36:43 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/17 11:37:51 by cylemair         ###   ########.fr       */
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
	char		*cmd;
	char		**paths;
	char		**args;
	pid_t		*pid;

	char		*prompt;
	char		**real_env;
	char		*cmd_out;
}				t_sh;

typedef struct  s_built
{
	void		(*f)(struct s_sh *);
	char		*name;
}				t_built;

char        **copy_array(char **array);
char		*findenv(char	**env, char *var);
char		**delenv(char **env, char *var);
char		**addenv(char **env, char *var);
char		**change_key(char **env, char *var);

char		*build_path(t_sh ell);
int			exec_cmd(t_sh ell, char *path);
void   		read_stdin(t_sh ell);
void    	change_dir(const char *path, t_sh *ell);
int		    check_builtin(t_sh *ell);
int			get_var(t_sh *ell);
int			tilt(t_sh *ell);

void		builtin_env(t_sh *ell);
void		builtin_unsetenv(t_sh *ell);
void		builtin_setenv(t_sh *ell);
void		builtin_cd(t_sh *ell);
void		builtin_echo(t_sh *ell);

void		putab(char **array);
void		puterror(char *error);
int			array_len(char **array);
void		streplace(char **s1, char **s2);
void		free_array(char **array);

#endif