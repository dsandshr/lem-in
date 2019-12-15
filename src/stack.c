/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:33:27 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/15 17:25:58 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			delete(t_set_path **stack)
{
	t_set_path	*tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	tmp = NULL;
}

void			push(t_set_path **stack, int id)
{
	t_set_path *tmp;

	tmp = *stack;
	if (*stack == NULL)
	{
		*stack = (t_set_path *)malloc(sizeof(t_set_path));
		(*stack)->var = id;
		(*stack)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_set_path *)malloc(sizeof(t_set_path));
	tmp->next->var = id;
	tmp->next->next = NULL;
}

void			rev_push(t_set_path **stack, int id)
{
	t_set_path *tmp;

	tmp = *stack;
	if (*stack == NULL)
	{
		*stack = (t_set_path *)malloc(sizeof(t_set_path));
		(*stack)->var = id;
		(*stack)->next = NULL;
		return ;
	}
	tmp = (t_set_path *)malloc(sizeof(t_set_path));
	tmp->var = id;
	tmp->next = *stack;
	*stack = tmp;
}