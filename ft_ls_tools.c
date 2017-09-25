/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:17:25 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 12:52:31 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				listeinit(t_ls *ls, int argc, char **argv)
{
	ls->flags = 0;
	ls->argc = argc;
	ls->argv = argv;
	ls->argv_i = 1;
	ls->first = NULL;
	ls->first_arg = NULL;
	ls->pos = 0;
	ls->numarg = 0;
	ls->erorrs = NULL;
}

t_lsl				*ft_ls_delete_list(t_lsl *list)
{
	t_lsl			*tmp;

	while (list)
	{
		ft_memdel((void**)&list->name);
		ft_memdel((void**)&list->permis);
		ft_memdel((void**)&list->owner);
		ft_memdel((void**)&list->group);
		ft_memdel((void**)&list->chemin);
		tmp = list->next;
		ft_memdel((void**)&list);
		list = tmp;
	}
	list = NULL;
	return (list);
}

char				*get_real_name(char *str)
{
	int				i;
	int				v;

	i = 0;
	v = 0;
	if (ft_strcmp(str, "./") > 0)
	{
		if (ft_strchr(str, '/') == NULL)
			return (str);
		while (str[i++] != '\0')
			if (str[i] == '/')
				v = i + 1;
		return (ft_strsdup(str, v));
	}
	else
		return (ft_strdup(str));
}

char				*ft_ls_get_chemin(char *chemin, char *name)
{
	int				i;
	char			*final;

	i = 0;
	while (chemin[i + 1] != '\0')
		i++;
	if (chemin[i] == '/')
		final = ft_strjoin(chemin, name);
	else
	{
		final = ft_strjoin(chemin, "/");
		final = ft_strjoin(final, name);
	}
	return (final);
}

int					count_t_lsl(t_lsl *list)
{
	int				i;

	i = 0;
	while (list != NULL)
	{
		i++;
		list = list->next;
	}
	return (i);
}
