/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:33:27 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/10 16:34:46 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			delete(s_set_path **stack)
{
	s_set_path	*tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	tmp = NULL;
}

void			push(s_set_path **stack, int id)
{
	s_set_path *tmp;

	tmp = *stack;
	if (*stack == NULL)
	{
		*stack = (s_set_path *)malloc(sizeof(s_set_path));
		(*stack)->var = id;
		(*stack)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (s_set_path *)malloc(sizeof(s_set_path));
	tmp->next->var = id;
	tmp->next->next = NULL;
}
