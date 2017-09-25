/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:26:14 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 11:51:02 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					affichageargg(t_ls *ls, char *chemin)
{
	if (((ls->flags & FLAG_R) && ls->pos > 0) || ls->numarg > 1)
		ft_printf("%s:\n", chemin);
	ls->pos++;
	return (1);
}

int					affichagebig(t_ls *ls, t_lsl *list)
{
	t_lsl			*listcpy;

	listcpy = list;
	if (ls->flags & FLAG_LV)
		affichagebig_l(listcpy);
	else
		while (listcpy != NULL)
		{
			ft_putstr(listcpy->name);
			ft_putstr("\n");
			listcpy = listcpy->next;
		}
	return (1);
}

int					affichagebig_file(t_ls *ls, t_lsl *list)
{
	t_lsl			*listcpy;

	listcpy = list;
	if (ls->flags & FLAG_LV)
		affichagebig_file_l(listcpy);
	else
	{
		ft_putstr(listcpy->chemin);
		ft_putstr("\n");
		listcpy = listcpy->next;
	}
	return (1);
}
