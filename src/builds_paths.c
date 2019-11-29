#include "lem_in.h"

s_paths *fill_paths(s_ferm **ferm, int end)
{
	int parent;
	s_paths		*path;

	path = (s_paths *)malloc(sizeof(s_paths));
	path->next = NULL;
	path->len = 0;
	path->go = OPEN;
	path->set = NULL;
	parent = 0;
	while (ferm[end][end].type != START)
	{
		add_num(end, &path->set, &path->s_set);
		ferm[parent][parent].split = -1;
		parent = ferm[end][end].parent;
		end = parent;
		path->len++;
	}
	add_num(end, &path->set, &path->s_set);
	path->len++;
	return (path);
}

s_paths *bfs_for_build(s_info *info, s_ferm **ferm)
{
	int branch;
	int room;
	s_set_path *stack;

	stack = NULL;
	branch = 0;
	room = 0;
	while (ferm[branch][branch].type != START)
		branch++;
	push(&stack, branch);
	while (stack)
	{
		branch = stack->var;
		delete(&stack);
		while (room < info->c_rooms)
		{
			if (ferm[branch][room].pass == OPEN && ferm[room][room].visit == 0)
			{
				push(&stack, room);
				ferm[room][room].parent = branch;
				ferm[room][room].visit = 1;
				if (ferm[room][room].type == END)
				{
					while(stack)
						delete(&stack);
					return (fill_paths(ferm, room));
				}
			}
			room++;
		}
		room = 0;
	}
	return (NULL);
}

void build_update(s_ferm **ferm, s_info *info)
{
	int branch;
	int room;

	room = 0;
	branch = 0;
	while (branch < info->c_rooms)
	{
		while (room < info->c_rooms)
		{
			if (ferm[room][room].split != -1)
			{
				ferm[branch][room].parent = 0;
				ferm[branch][room].visit = 0;
			}
			room++;
		}
		room = 0;
		branch++;
	}
}

s_paths	*build_paths(s_ferm **ferm, s_info *info, int c_paths)
{
	s_paths *paths;
	s_paths *save;
	int i;

	i = 0;
	paths = NULL;
	while (i < c_paths)
	{
		if (paths == NULL)
		{
			paths = bfs_for_build(info, ferm);
			save = paths;
		}
		else
		{
			paths->next = bfs_for_build(info, ferm);
			paths = paths->next;
		}
		build_update(ferm, info);
		if (paths == NULL)
		{
			delete_paths(&save);
			return (NULL);
		}
		i++;
	}
	return (save);
}