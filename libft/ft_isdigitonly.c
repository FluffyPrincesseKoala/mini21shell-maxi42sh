/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigitonly.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:28:47 by cylemair          #+#    #+#             */
/*   Updated: 2019/10/19 16:28:48 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isdigitonly(char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	if (str[0] && (str[0] == '-' || str[0] == '+'))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (0);
		i++;
	}
	return (1);
}
