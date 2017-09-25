/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_s1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybitton <ybitton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:24:19 by ybitton           #+#    #+#             */
/*   Updated: 2017/05/02 14:50:14 by ybitton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				reverse_list(t_lsl **ls)
{
	t_lsl			*prev;
	t_lsl			*current;
	t_lsl			*next;

	prev = NULL;
	current = *ls;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*ls = prev;
}
