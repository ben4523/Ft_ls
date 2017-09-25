/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_resolve_recursive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:28:11 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 14:13:32 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lsl				*put_in_list(struct dirent *lu,
						t_lsl *list_off, t_ls *ls, char *chemin)
{
	t_lsl			*list;

	if (lu->d_name[0] == '.' && !(ls->flags & FLAG_A || ls->flags & FLAG_F))
		return (list_off);
	list = ft_memalloc(sizeof(t_lsl));
	list->next = NULL;
	list->chemin = ft_strdup(chemin);
	list = put_in_list_suite(list, ft_ls_get_chemin(chemin,
								lu->d_name), ls, lu);
	if (list == NULL)
		return (list_off);
	if (list_off == NULL)
		return (list);
	else
		return (ft_ls_list_add(list_off, list));
}

t_lsl				*put_in_list_suite(t_lsl *list, char *chemin,
						t_ls *ls, struct dirent *lu)
{
	struct stat		sb;
	struct passwd	*pw;
	struct group	*gr;

	if (lstat(chemin, &sb) == -1 && (ls->erorrs =
			add_error_arg_lst(ls, lu->d_name)))
		return (NULL);
	if (S_ISLNK(sb.st_mode) && (ls->flags & FLAG_LV))
		list->name = get_name_link(chemin, sb, lu);
	else
		list->name = ft_strdup(lu->d_name);
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
	list->blocks_size = sb.st_blocks;
	return (list);
}

void				ft_ls_open(t_ls *ls, char *chemin, char *name)
{
	DIR				*d;
	t_lsl			*list;
	t_lsl			*list_cpy;
	struct dirent	*lu;

	lu = NULL;
	list = NULL;
	if ((d = opendir(chemin)) != NULL && affichageargg(ls, chemin))
	{
		while ((lu = readdir(d)) != NULL)
			list = put_in_list(lu, list, ls, chemin);
		affichage_error_arg_lst(ls);
		closedir(d);
		if (flag_sort(&list, ls) &&
				affichagebig(ls, list) && (ls->flags & FLAG_R))
		{
			list_cpy = list;
			ft_ls_open_suite(ls, chemin, list_cpy);
		}
		list = ft_ls_delete_list(list);
	}
	else if (affichageargg(ls, chemin))
		ft_ls_basicerror("ls: ", name, 0);
}

void				ft_ls_open_suite(t_ls *ls, char *chemin, t_lsl *list_cpy)
{
	while (list_cpy != NULL)
	{
		if (list_cpy->type == 1 && ft_strcmp(".", list_cpy->name)
			&& ft_strcmp("..", list_cpy->name))
		{
			ft_putchar('\n');
			ft_ls_open(ls, ft_ls_get_chemin(chemin, list_cpy->name),
						list_cpy->name);
			list_cpy = list_cpy->next;
		}
		else
			list_cpy = list_cpy->next;
	}
}

t_lsl				*ft_ls_list_add(t_lsl *list_off, t_lsl *list)
{
	t_lsl			*list_tmp;

	list_tmp = list_off;
	while (list_tmp->next != NULL)
		list_tmp = list_tmp->next;
	list_tmp->next = list;
	return (list_off);
}
