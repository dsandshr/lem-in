/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builds_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:22:41 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/10 20:05:41 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

s_paths		*fill_paths(s_ferm *ferm, int end)
{
	int		parent;
	s_paths	*path;

	path = (s_paths *)malloc(sizeof(s_paths));
	path->next = NULL;
	path->len = 0;
	path->go = OPEN;
	path->set = NULL;
	path->s_set = NULL;
	parent = 0;
	while (ferm[end].matrix[end].type != END)
	{
		parent = ferm[end].matrix[end].parent;
		ferm[end].matrix[parent].pass = TMP_CLOSE;
		ferm[parent].matrix[end].pass = TMP_CLOSE;
		add_num(end, &path->set, &path->s_set);
		end = parent;
		path->len++;
	}
	add_num(end, &path->set, &path->s_set);
	path->len++;
	return (path);
}

void		add_paths(s_bfb *bfb, s_ferm *ferm)
{
	if (bfb->paths == NULL)
	{
		bfb->paths = fill_paths(ferm, bfb->room);
		bfb->save = bfb->paths;
	}
	else
	{
		(bfb->paths)->next = fill_paths(ferm, bfb->room);
		bfb->paths = (bfb->paths)->next;
	}
}

int			create_paths(s_bfb *bfb, s_ferm *ferm, s_info *info, int start)
{
	if (ferm[bfb->room].matrix[bfb->room].type == START)
	{
		add_paths(bfb, ferm);
		update_ferm(ferm, info);
		bfb->branch = start;
		bfb->room = -1;
		while (bfb->stack)
			delete(&(bfb->stack));
		if (bfb->paths == NULL)
		{
			delete_paths(&(bfb->save));
			return (0);
		}
	}
	return (1);
}

void		init_bfb(s_bfb *bfb, int start)
{
	bfb->branch = start;
	bfb->room = 0;
	bfb->paths = NULL;
	bfb->save = NULL;
	bfb->stack = NULL;
	push(&(bfb->stack), bfb->branch);
}

s_paths		*bfs_for_build(s_info *info, s_ferm *ferm, int start)
{
	s_bfb	bfb;

	init_bfb(&bfb, start);
	while (bfb.stack)
	{
		bfb.branch = bfb.stack->var;
		delete(&(bfb.stack));
		while (bfb.room < info->c_rooms)
		{
			if (ferm[bfb.branch].matrix[bfb.room].pass == TMP_OPEN \
			&& ferm[bfb.room].matrix[bfb.room].visit == 0)
			{
				if (ferm[bfb.room].matrix[bfb.room].type != START)
					push(&(bfb.stack), bfb.room);
				if (ferm[bfb.room].matrix[bfb.room].type != START)
					ferm[bfb.room].matrix[bfb.room].visit = 1;
				ferm[bfb.room].matrix[bfb.room].parent = bfb.branch;
				if (!create_paths(&bfb, ferm, info, start))
					return (NULL);
			}
			bfb.room++;
		}
		bfb.room = 0;
	}
	return (bfb.save);
}
