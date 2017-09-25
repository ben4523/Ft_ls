/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:05:30 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 11:49:57 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_ls_pars(t_ls *ls)
{
	int				i;

	i = 1;
	while (ls->argv[i] && ft_strchr(ls->argv[i], '-') &&
			ls->argv[i][1] && ft_strcmp(ls->argv[i], "--") != 0
			&& ls->argv_i++ && ls->argc--)
		ft_ls_pars_flags(ls, i++);
	if (ls->argv[i] && ft_strcmp(ls->argv[i], "--") == 0 && ls->argv_i++)
		ls->argc--;
	if ((ls->flags != 0 && ls->argc >= 1) || ls->flags == 0)
		ft_ls_pars_files(ls);
	return (1);
}

void				ft_ls_pars_flags(t_ls *ls, int v)
{
	int				i;

	i = 0;
	while (ls->argv[v][++i] != '\0')
	{
		if (ls->argv[v][i] == 'l')
			ls->flags |= FLAG_LV;
		else if (ls->argv[v][i] == 'R')
			ls->flags |= FLAG_R;
		else if (ls->argv[v][i] == 'r')
			ls->flags |= FLAG_RR;
		else if (ls->argv[v][i] == 'a')
			ls->flags |= FLAG_A;
		else if (ls->argv[v][i] == 't')
			ls->flags |= FLAG_T;
		else if (ls->argv[v][i] == 'f')
			ls->flags |= FLAG_F;
		else if (ls->argv[v][i] == '1')
			;
		else
			ft_ls_error_arg(ls->argv[v][i]);
	}
}

void				ft_ls_pars_files(t_ls *ls)
{
	int				i;
	int				v;

	if ((ls->flags != 0 && ls->argc == 1) ||
		(ls->flags == 0 && ls->argc <= 1))
	{
		ls->first_arg = ft_memalloc(sizeof(t_lsl));
		ls->first_arg->name = ft_strdup(".");
		ls->first_arg->chemin = ft_strdup(".");
		ls->first_arg->type = 1;
		ls->numarg++;
	}
	else
	{
		i = 0;
		v = ls->argv_i;
		while (i++ + 1 < ls->argc)
			if (!ft_strcmp(ls->argv[v++], ""))
				ft_ls_basicerror("ls: fts_open: No such file or directory\n"
									, "", 4);
		i = 0;
		ft_ls_pars_files_suite(ls, i);
	}
}

void				ft_ls_pars_files_suite(t_ls *ls, int i)
{
	t_lsl			*tmp;

	while (i++ + 1 < ls->argc)
	{
		ls->first = put_in_list_first(ls);
		ls->numarg++;
	}
	affichage_error_arg_lst(ls);
	flag_sort(&ls->first, ls);
	ft_sort_folders_files(&ls->first);
	tmp = ls->first;
	i = 0;
	while ((tmp != NULL) && (tmp->next != NULL) && ((tmp->next->type != 1)))
	{
		i++;
		tmp = tmp->next;
	}
	ft_ls_pars_files_suite1(ls, i, tmp);
}
