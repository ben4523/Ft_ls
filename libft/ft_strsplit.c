/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:30:04 by ybitton           #+#    #+#             */
/*   Updated: 2016/12/16 17:39:21 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t		ftstrlenword(const char *str, int start, char stop)
{
	size_t		count;

	if (!str)
		return (0);
	count = 0;
	while (str[start] && (str[start] != stop))
	{
		start++;
		count++;
	}
	return (count);
}

static size_t		ft_strsplitlen(char const *s, char caract)
{
	int				count;
	int				tab_num;
	char			*str;
	int				ok;

	str = (char*)s;
	count = 0;
	tab_num = 0;
	while (str[count++])
	{
		ok = 0;
		while ((str[count] != (char)caract) && str[count])
		{
			if (ok == 0)
			{
				ok = 1;
				tab_num++;
			}
			if (str[count + 1])
				count++;
			else
				return (tab_num);
		}
	}
	return (tab_num);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**d;
	char			*str;
	int				i;
	int				count;
	int				tab_num;

	str = (char *)s;
	if (!str)
		return (NULL);
	tab_num = ft_strsplitlen(s, c);
	if (!(d = (char**)malloc(sizeof(*d) * (tab_num + 1))))
		return (NULL);
	i = 0;
	count = 0;
	while (i < tab_num)
	{
		while ((str[count] == (char)c) && str[count])
			count++;
		d[i] = ft_strsub(str, count, ftstrlenword(str, count, c));
		while ((str[count] != (char)c) && str[count])
			count++;
		i++;
	}
	d[i] = NULL;
	return (d);
}
