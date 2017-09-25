/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:16:54 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/02 14:35:51 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				*ft_ls_basicerror(char *name, char *error, int ex)
{
	ft_putstr_fd(name, 2);
	if (ex != 4)
		perror(error);
	if (ex)
		exit(EXIT_FAILURE);
	return (NULL);
}

void				ft_ls_error_arg(char arg)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(arg, 2);
	ft_putstr_fd("\nusage: ft_ls [-Rafglrtu1] [file ...]\n", 2);
	exit(EXIT_FAILURE);
}

void				affichage_error_arg_lst(t_ls *ls)
{
	ft_sort_ascii(&ls->erorrs);
	while (ls->erorrs != NULL)
	{
		ft_ls_basicerror("ls: ", ls->erorrs->name, 0);
		ft_memdel((void**)&ls->erorrs->name);
		ls->erorrs = ls->erorrs->next;
	}
	ft_memdel((void**)&ls->erorrs);
	ls->erorrs = NULL;
}

t_lsl				*add_error_arg_lst(t_ls *ls, char *s)
{
	t_lsl			*list;

	if (!(list = ft_memalloc(sizeof(t_lsl))))
		return (ls->erorrs);
	if (s != NULL)
		list->name = ft_strdup(s);
	list->next = NULL;
	if (ls->erorrs != NULL)
		return (ft_ls_list_add(ls->erorrs, list));
	else
		return (list);
}
