#include "lem_in.h"

void update_ferm(s_ferm **ferm, s_info *info)
{
	int branch;
	int room;

	room = 0;
	branch = 0;
	while (branch < info->c_rooms)
	{
		while (room < info->c_rooms)
		{
			ferm[branch][room].parent = 0;
			ferm[branch][room].visit = 0;
			room++;
		}
		room = 0;
		branch++;
	}
}

s_paths *mark_the_path(s_ferm **ferm, int end, s_info *info)
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
		parent = ferm[end][end].parent;
		ferm[end][parent].pass = OPEN;
		ferm[parent][end].pass = CLOSE;
		if (ferm[parent][parent].type != START)
			ferm[parent][parent].split++;
		end = parent;
		path->len++;
	}
	add_num(end, &path->set, &path->s_set);
	path->len++;
	update_ferm(ferm, info);
	return (path);
}

int	mark_rooms(s_ferm **ferm, int branch, int room, s_set_path **stack)
{
	int parent;

	parent = ferm[branch][branch].parent;
	if (ferm[parent][parent].split == 0 && ferm[branch][branch].split > 0 && ferm[room][room].split == 0)
		return (1);
	push(stack, room);
	ferm[room][room].parent = branch;
	ferm[room][room].visit = 1;
	if (ferm[room][room].type == END)
	{
		while(*stack)
			delete(stack);
		return (END);
	}
	return (1);
}

s_paths *bfs(s_info *info, s_ferm **ferm)
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
		while (room < info->c_rooms && branch < info->c_rooms)
		{
			if (ferm[branch][room].pass == OPEN && ferm[room][room].visit == 0)
			{
				if ((mark_rooms(ferm, branch, room, &stack)) == END)
					return (mark_the_path(ferm, room, info));
			}
			room++;
		}
		room = 0;
	}
	return (NULL);
}

s_paths *search_paths(s_info *info, s_ferm **ferm, int c_paths)
{
	s_paths *paths;
	s_paths *save;
	int i;

	paths = NULL;
	i = 0;
	while (i < c_paths)
	{
		if (paths == NULL)
		{
			paths = bfs(info, ferm);
			if (paths == NULL)
				return (NULL);
			save = paths;
		}
		else
		{
			paths->next = bfs(info, ferm);
			if (paths->next == NULL)
			{
				delete_paths(&paths);
				return (NULL);
			}
			paths = paths->next;
		}
		i++;
	}
	return (save);
}