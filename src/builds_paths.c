/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builds_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:22:41 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/07 19:51:13 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

s_paths	*fill_paths(s_ferm *ferm, int end)
{
	int parent;
	s_paths		*path;

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
		// if (ferm[parent].matrix[parent].split == -1)
		// {
		// 	delete_paths(&path);
		// 	return (NULL);
		// }
		add_num(end, &path->set, &path->s_set);
		// if (ferm[parent].matrix[parent].type != START && ferm[parent].matrix[parent].type != END)
		// 	ferm[parent].matrix[parent].split = -1;
		end = parent;
		path->len++;
	}
	add_num(end, &path->set, &path->s_set);
	path->len++;
	return (path);
}

s_paths	*bfs_for_build(s_info *info, s_ferm *ferm, int start)
{
	int branch;
	int room;
	s_set_path *stack;
	s_paths *paths;
	s_paths *save;

	paths = NULL;
	stack = NULL;
	save = NULL;
	branch = start;
	room = 0;
	push(&stack, branch);
	while (stack)
	{
		branch = stack->var;
		delete(&stack);
		while (room < info->c_rooms)
		{
			if (ferm[branch].matrix[room].pass == TMP_OPEN && ferm[room].matrix[room].visit == 0) //&& ferm[room].matrix[room].split != -1)
			{
				if (ferm[room].matrix[room].type != END && ferm[room].matrix[room].type != START)
				{
					push(&stack, room);
					ferm[room].matrix[room].visit = 1;
				}
				ferm[room].matrix[room].parent = branch;
				if (ferm[room].matrix[room].type == START)
				{
					if (paths == NULL)
					{
						paths = fill_paths(ferm, room);
						save = paths;
					}
					else
					{
						paths->next = fill_paths(ferm, room);
						paths = paths->next;
					}
					update_ferm(ferm, info);
					branch = start;
					room = -1;
					while (stack)
							delete(&stack);
					if (paths == NULL)
					{
						delete_paths(&save);
						return (NULL);
					}
				}
			}
			room = room + 1;
		}
		room = 0;
	}
	return (save);
}
