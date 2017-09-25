/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:25:07 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/02 14:43:21 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					calc_size(t_lsl *list, char *champ)
{
	int				saved;
	int				tmp;
	t_lsl			*list_cpy;

	saved = 0;
	tmp = 0;
	list_cpy = list;
	while (list_cpy != NULL)
	{
		if (!ft_strcmp(champ, "owner"))
			tmp = (int)ft_strlen(list_cpy->owner);
		if (!ft_strcmp(champ, "group"))
			tmp = (int)ft_strlen(list_cpy->group);
		if (!ft_strcmp(champ, "links"))
			tmp = (int)ft_strlen(ft_itoa(list_cpy->links));
		if (!ft_strcmp(champ, "octets"))
			tmp = (int)ft_strlen(ft_itoa(list_cpy->octets));
		if (tmp > saved)
			saved = tmp;
		list_cpy = list_cpy->next;
	}
	return (saved);
}

long long			calc_total_blocks(t_lsl *list)
{
	long long		block_total;
	t_lsl			*list_cpy;

	list_cpy = list;
	block_total = 0;
	while (list_cpy != NULL)
	{
		block_total += list_cpy->blocks_size;
		list_cpy = list_cpy->next;
	}
	return (block_total);
}

void				list_size_init(t_size *size_list, t_lsl *list)
{
	size_list->link_size = calc_size(list, "links");
	size_list->owner_size = calc_size(list, "owner");
	size_list->group_size = calc_size(list, "group");
	size_list->octets_size = calc_size(list, "octets");
	size_list->total = calc_total_blocks(list);
}

int					space_one(int max_size, int space, int num_size)
{
	return ((max_size + space) - num_size);
}
