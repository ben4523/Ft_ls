/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display_s1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:40:38 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/03 11:46:52 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				affichagebig_l(t_lsl *list)
{
	t_size			sizel;
	int				i;

	list_size_init(&sizel, list);
	if (list != NULL)
		ft_printf("total %lld\n", sizel.total);
	while (list != NULL)
	{
		ft_putstr(list->permis);
		i = 0;
		while (i++ < space_one(sizel.link_size, 2,
				(int)ft_strlen(ft_itoa(list->links))))
			ft_putstr(" ");
		ft_putnbr(list->links);
		i = 0;
		while (i++ < space_one(sizel.owner_size, 1,
				(int)ft_strlen(list->owner)))
			ft_putstr(" ");
		ft_putstr(list->owner);
		i = 0;
		affichagebig_l_suite(list, sizel, i);
		list = list->next;
	}
}

void				affichagebig_l_suite(t_lsl *list, t_size sizel, int i)
{
	while (i++ < space_one(sizel.group_size, 2,
			(int)ft_strlen(list->group)))
		ft_putstr(" ");
	ft_putstr(list->group);
	i = 0;
	while (i++ < space_one(sizel.octets_size, 2,
			(int)ft_strlen(ft_itoa(list->octets))))
		ft_putstr(" ");
	ft_printf("%ld %s %s\n", list->octets, list->times, list->name);
}

void				affichagebig_file_l(t_lsl *list)
{
	t_size			sizel;
	int				i;

	list_size_init(&sizel, list);
	ft_putstr(list->permis);
	i = 0;
	while (i++ < space_one(sizel.link_size, 2,
			(int)ft_strlen(ft_itoa(list->links))))
		ft_putstr(" ");
	ft_putnbr(list->links);
	i = 0;
	while (i++ < space_one(sizel.owner_size, 1,
			(int)ft_strlen(list->owner)))
		ft_putstr(" ");
	ft_putstr(list->owner);
	i = 0;
	while (i++ < space_one(sizel.group_size, 2,
			(int)ft_strlen(list->group)))
		ft_putstr(" ");
	ft_putstr(list->group);
	i = 0;
	while (i++ < space_one(sizel.octets_size, 2,
			(int)ft_strlen(ft_itoa(list->octets))))
		ft_putstr(" ");
	ft_printf("%ld %s %s\n", list->octets, list->times, list->chemin);
}
