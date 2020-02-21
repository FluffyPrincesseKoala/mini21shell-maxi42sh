/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:36:56 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/20 23:46:54 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	format_stdin(t_sh *ell)
{
	t_vect	*cmds;
	char	**tab;
	char	**args;
	char	*line;
	int		i;

	i = 0;
	cmds = NULL;
	line = NULL;
	line = replace_delim((*ell).cmd, '\t', ' ');
	tab = ft_strsplit((line) ? line : (*ell).cmd, ';');
	while (tab[i])
	{
		args = ft_strsplit(tab[i], ' ');
		if (cmds != NULL && args[0])
			vect_add(&cmds, vect_new(args));
		else if (args[0])
			cmds = vect_new(args);
		free_array(args);
		i++;
	}
    free_array(tab);
    ft_strdel(&line);
    //ft_strdel(&(*ell).cmd);
	get_var(&cmds, (*ell).env);
	tilt(&cmds, *ell);
	(*ell).cmds = cmds;
}

static int	browse_cmd(t_sh *ell)
{
	t_vect	*lst;
	char	*tmp;
	int		ret;

	lst = (*ell).cmds;
	ret = 0;
	while (ret != -2 && lst)
	{
		ret = 0;
		if ((ret = check_builtin(&(*ell), lst)) == 0)
		{
			if ((tmp = build_path((*ell), lst)))
				ret = exec_cmd((*ell), tmp, lst);
			else if (!tmp && !access((const char*)lst->arg[0], X_OK))
				ret = exec_cmd((*ell), lst->arg[0], lst);
			else
				ret = -1;
			ft_strdel(&tmp);
		}
		puterror((ret == -1) ? "commande inconnue...\n" : NULL);
		lst = (ret != -2) ? lst->next : lst;
	}
	if (ret == -2 && lst->next)
		puterror("Il y a des tâches stoppées.\n");
	return (ret);
}

char				*str_join_free(char **s1, char **s2)
{
	char			*new;

	if (s1 && s2 && *s1 && *s2)
	{
		if (!(new = malloc(sizeof(char) * (ft_strlen(*s1)
			+ ft_strlen(*s2) + 1))))
			return (NULL);
		new = ft_strcpy(new, *s1);
		new = ft_strcat(new, *s2);
		ft_strdel(s1);
		ft_strdel(s2);
	}
	else if (!*s1)
	{
		new = ft_strdup(*s2);
		ft_strdel(s2);
	}
	else
	{
		new = ft_strdup(*s1);
		ft_strdel(s1);
	}
	return (new);
}

int					fd_parser(const int fd, char **line)
{
	char			buffer[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	if ((ret = read(fd, buffer, BUFF_SIZE)) < 0)
		return (-1);
	buffer[ret] = '\0';
	*line = ft_strdup(buffer);
	while (ret > 0 && !(ft_strchr(*line, '\n')))
	{
		if ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
		{
			buffer[ret] = '\0';
			tmp = ft_strdup(buffer);
			*line = str_join_free(line, &tmp);
		}
	}
	return (ret);
}

int					strchri(char *str, char c)
{
	int				i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int					gnl(const int fd, char **line)
{
	static	char	*str;
	static	int		ret;
	char			*tmp;

	if (fd <= -1 || line == NULL)
		return (-1);
	if ((ret = fd_parser(fd, line)) <= -1)
		return (-1);
	tmp = str_join_free(&str, line);
	if (ft_strchr(tmp, '\n') && ft_strchr(tmp, '\n') + 1)
		str = ft_strdup(ft_strchr(tmp, '\n') + 1);
	*line = ft_strsub(tmp, 0, strchri(tmp, '\n'));
    if (ft_strchr(tmp, '\n') && ft_strchr(tmp, '\n') + 1)
	    ft_strdel(&str);
	ft_strdel(&tmp);
	return ((ft_strlen(*line) || ret || str) ? 1 : ret);
}

void		read_stdin(t_sh ell)
{
	int		built;

	built = 0;
	while (built != -2)
	{
		ft_putstr(ell.prompt);
		gnl(0, &(ell.cmd));
		if (ft_strcmp(ell.cmd, ""))
		{
			format_stdin(&ell);
			if (count_delim(ell.cmd, ';') > count_lst(ell.cmds))
				puterror("erreur de syntaxe\n");
			else
				built = browse_cmd(&ell);
			free_vector(&ell.cmds);
		}
    	ft_strdel(&(ell.cmd));
	}
    if (ell.env != ell.venv && ell.env)
        free_array(ell.env);
}
