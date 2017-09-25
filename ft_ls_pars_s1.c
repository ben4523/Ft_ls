/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_pars_s1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:10:51 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 11:45:48 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_ls_pars_files_suite1(t_ls *ls, int i, t_lsl *tmp)
{
	if (i >= 1)
	{
		ls->first_arg = (tmp != NULL) ? tmp->next : NULL;
		if (tmp != NULL)
			tmp->next = NULL;
		flag_sort(&ls->first, ls);
	}
	else
	{
		if (tmp && tmp->next == NULL && (tmp->type != 1))
			ls->first_arg = NULL;
		else
		{
			ls->first_arg = ls->first;
			ls->first = NULL;
		}
	}
}

t_lsl				*put_in_list_first(t_ls *ls)
{
	t_lsl			*list;
	struct stat		sb;

	if (lstat(ls->argv[ls->argv_i], &sb) == -1)
	{
		ls->erorrs = add_error_arg_lst(ls, ls->argv[ls->argv_i++]);
		return (ls->first);
	}
	if (S_ISLNK(sb.st_mode))
		if (stat(ls->argv[ls->argv_i], &sb) == -1)
		{
			ls->erorrs = add_error_arg_lst(ls, ls->argv[ls->argv_i++]);
			return (ls->first);
		}
	if (!(list = ft_memalloc(sizeof(t_lsl))))
		return (ls->first);
	list->chemin = ft_strdup(ls->argv[ls->argv_i]);
	ls->argv_i++;
	list->name = get_real_name(list->chemin);
	return (put_in_list_first_suite(ls, list, sb));
}

t_lsl				*put_in_list_first_suite(t_ls *ls,
					t_lsl *list, struct stat sb)
{
	if (ls->flags & FLAG_LV)
		put_in_list_first_s1(list, sb);
	else
	{
		list->next = NULL;
		list->type = ft_ls_type_files(sb);
	}
	if (ls->first == NULL)
		return (list);
	else
		return (ft_ls_list_add(ls->first, list));
}

void				put_in_list_first_s1(t_lsl *list, struct stat sb)
{
	struct passwd	*pw;
	struct group	*gr;

	list->next = NULL;
	pw = getpwuid(sb.st_uid);
	gr = getgrgid(sb.st_gid);
	list->permis = ft_ls_permisson(sb);
	list->links = (long)sb.st_nlink;
	list->owner = ft_strdup(pw->pw_name);
	list->group = ft_strdup(gr->gr_name);
	list->octets = (long long)sb.st_size;
	list->times_last_modif = sb.st_mtime;
	list->times_last_acces = sb.st_atime;
	list->times_last_change = sb.st_ctime;
	list->times = ft_ls_times_l(sb.st_mtime);
	list->type = ft_ls_type_files(sb);
}
