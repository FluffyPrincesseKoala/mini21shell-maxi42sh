/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 19:22:09 by lgaveria          #+#    #+#             */
/*   Updated: 2017/01/10 22:45:32 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ctwords(char const *s, char delim)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != delim)
			if (s[i + 1] == delim || !s[i + 1])
				count += 1;
		i += 1;
	}
	return (count);
}

static int		ctchar(char const *s, char delim)
{
	int	count;

	count = 0;
	while (s[count] != delim && s[count])
		count += 1;
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		i;
	int		j;
	int		k;

	if (!s || (ret = malloc(sizeof(char *) * (ctwords(s, c) + 1))) == 0)
		return (0);
	k = -1;
	i = 0;
	j = 0;
	while (s[++k])
	{
		j = (s[k] == c) ? 0 : j;
		if (s[k] != c)
		{
			if (j == 0)
				if ((ret[i] = malloc(sizeof(char) * ctchar(&s[k], c) + 1)) == 0)
					return (0);
			ret[i][j++] = s[k];
			ret[i][j] = '\0';
		}
		i += ((s[k + 1] == c || !s[k + 1]) && j != 0) ? 1 : 0;
	}
	ret[i] = NULL;
	return (ret);
}
