/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:41:15 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 12:16:55 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					main(int argc, char **argv)
{
	t_ls			ls;
	int				i;

	listeinit(&ls, argc, argv);
	ft_ls_pars(&ls);
	i = 0;
	while (ls.first != NULL && affichagebig_file(&ls, ls.first))
	{
		i++;
		ls.first = ls.first->next;
	}
	ls.first = ft_ls_delete_list(ls.first);
	if (ls.first_arg != NULL && i > 1)
		ft_putchar('\n');
	while (ls.first_arg != NULL)
	{
		ft_ls_open(&ls, ls.first_arg->chemin, ls.first_arg->name);
		if (ls.first_arg->next != NULL)
			ft_putchar('\n');
		ls.first_arg = ls.first_arg->next;
	}
	ls.first_arg = ft_ls_delete_list(ls.first_arg);
	return (1);
}
