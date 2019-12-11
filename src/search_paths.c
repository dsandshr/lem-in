/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:03:18 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/11 16:29:29 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				mark_the_path(t_ferm *ferm, int end)
{
	int			parent;

	while (ferm[end].matrix[end].type != START)
	{
		parent = ferm[end].matrix[end].parent;
		if (ferm[parent].matrix[end].pass != TMP_OPEN)
		{
			ferm[end].matrix[parent].pass = TMP_OPEN;
			ferm[parent].matrix[end].pass = TMP_CLOSE;
		}
		else
		{
			ferm[end].matrix[parent].pass = TMP_CLOSE;
			ferm[parent].matrix[end].pass = TMP_CLOSE;
		}
		if (ferm[parent].matrix[parent].type != START\
		&& ferm[parent].matrix[parent].type != END)
			ferm[parent].matrix[parent].split = 1;
		end = parent;
	}
	return (1);
}

int				mark_rooms(t_ferm *ferm, int b, int room, t_set_path **stack)
{
	int			parent;

	parent = ferm[b].matrix[b].parent;
	ferm[room].matrix[room].visit = 1;
	if ((ferm[parent].matrix[b].pass == OPEN\
	|| ferm[parent].matrix[parent].type == START)\
	&& ferm[b].matrix[b].split == 1)
	{
		if (ferm[b].matrix[room].pass == OPEN\
		&& (split_vertex(ferm[b].links, ferm, b)) == 1)
			return (1);
	}
	push(stack, room);
	ferm[room].matrix[room].parent = b;
	if (ferm[room].matrix[room].type == END)
	{
		while (*stack)
			delete(stack);
		return (END);
	}
	return (1);
}

int				begin(t_set_path **stack, t_ferm *ferm, int branch)
{
	int			r;
	t_set_path	*links;

	while (*stack)
	{
		r = 0;
		branch = (*stack)->var;
		links = ferm[branch].links;
		delete(stack);
		while (links)
		{
			r = links->var;
			if ((ferm[branch].matrix[r].pass == TMP_OPEN\
			|| ferm[branch].matrix[r].pass == OPEN) && r != branch)
			{
				if (ferm[r].matrix[r].visit == 0 && ferm[r].matrix[r].type != 1)
				{
					if ((mark_rooms(ferm, branch, r, stack)) == END)
						return (mark_the_path(ferm, r));
				}
			}
			links = links->next;
		}
	}
	return (0);
}

int				bfs(t_info *info, t_ferm *ferm, int branch)
{
	int			room;
	int			c_room;
	t_set_path	*stack;

	stack = NULL;
	room = 0;
	c_room = info->c_rooms;
	ferm[branch].matrix[branch].visit = 1;
	push(&stack, branch);
	return (begin(&stack, ferm, branch));
}

int				search_paths(t_info *info, t_ferm *ferm, int c_paths, int start)
{
	int			i;

	i = 0;
	while (i < c_paths)
	{
		if (bfs(info, ferm, start) == 0)
		{
			update_ferm(ferm, info);
			return (0);
		}
		update_ferm(ferm, info);
		i++;
	}
	return (1);
}
