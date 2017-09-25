/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:23:00 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/02 15:35:17 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					flag_sort(t_lsl **list_off, t_ls *ls)
{
	if (!(ls->flags & FLAG_F))
		ft_sort_ascii(list_off);
	if (ls->flags & FLAG_RR)
		reverse_list(list_off);
	if (ls->flags & FLAG_T)
		ft_sort_flag_t(list_off);
	return (1);
}

void				help_sort(t_lsl **nd, t_lsl **nxt,
								t_lsl **prev, int *done)
{
	(*nd)->next = (*nxt)->next;
	(*nxt)->next = *nd;
	*prev = *nxt;
	*done = 0;
}

void				ft_sort_folders_files(t_lsl **lst)
{
	int				done;
	t_lsl			**prev;
	t_lsl			*nd;
	t_lsl			*nxt;

	done = 0;
	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	while (!done)
	{
		prev = lst;
		nd = *lst;
		nxt = (*lst)->next;
		done = 1;
		while (nxt)
		{
			if (nd->type == 1 && nxt->type != 1)
				help_sort(&nd, &nxt, prev, &done);
			prev = &nd->next;
			nd = nxt;
			nxt = nxt->next;
		}
	}
}

void				ft_sort_ascii(t_lsl **lst)
{
	int				done;
	t_lsl			**prev;
	t_lsl			*nd;
	t_lsl			*nxt;

	done = 0;
	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	while (!done)
	{
		prev = lst;
		nd = *lst;
		nxt = (*lst)->next;
		done = 1;
		while (nxt)
		{
			if (ft_strcmp(nd->name, nxt->name) > 0)
				help_sort(&nd, &nxt, prev, &done);
			prev = &nd->next;
			nd = nxt;
			nxt = nxt->next;
		}
	}
}

void				ft_sort_flag_t(t_lsl **lst)
{
	int				done;
	t_lsl			**prev;
	t_lsl			*nd;
	t_lsl			*nxt;

	done = 0;
	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	while (!done)
	{
		prev = lst;
		nd = *lst;
		nxt = (*lst)->next;
		done = 1;
		while (nxt)
		{
			if (nd->times_last_modif < nxt->times_last_modif)
				help_sort(&nd, &nxt, prev, &done);
			prev = &nd->next;
			nd = nxt;
			nxt = nxt->next;
		}
	}
}
