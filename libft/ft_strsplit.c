/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:37:46 by cylemair          #+#    #+#             */
/*   Updated: 2019/12/12 10:54:36 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_copy_str(char const *s, char c, size_t size_a, char **ret)
{
	size_t		i;
	size_t		len_str;

	i = 0;
	len_str = 0;
	while (i < size_a)
	{
		if (*s != c && *s != '\0')
			len_str++;
		else if (len_str)
		{
			if ((ret[i] = (char *)malloc(sizeof(**ret) * len_str + 1)) == NULL)
				return (1);
			ft_strncpy(ret[i], s - len_str, len_str);
			ret[i++][len_str] = '\0';
			len_str = 0;
		}
		s++;
	}
	return (0);
}

static int		count_words(char const *s, char c)
{
	int			count;

	count = 0;
	if (*s != c && *s)
	{
		s++;
		count++;
	}
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (*s != c && *s)
				count++;
		}
		s++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**ret;
	size_t		size_a;

	if (s == NULL)
		return (NULL);
	size_a = count_words(s, c);
	ret = (char **)malloc(sizeof(*ret) * (size_a + 1));
	if (ret == NULL)
		return (NULL);
	if (ft_copy_str(s, c, size_a, ret))
		return (NULL);
	ret[size_a] = NULL;
	return (ret);
}
