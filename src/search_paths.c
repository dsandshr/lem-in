#include "lem_in.h"

void update_ferm(s_ferm *ferm, s_info *info)
{
	int branch;
	int room;
	s_set_path *links;

	room = 0;
	branch = 0;
	while (branch < info->c_rooms)
	{
		links = ferm[branch].links;
		while (links)
		{
			room = links->var;
			ferm[branch].matrix[room].parent = 0;
			ferm[branch].matrix[room].visit = 0;
			links = links->next;
		}
		ferm[branch].matrix[branch].parent = 0;
		ferm[branch].matrix[branch].visit = 0;
		room = 0;
		branch++;
	}
}

int mark_the_path(s_ferm *ferm, int end)
{
	int parent;

	while (ferm[end].matrix[end].type != START)
	{
		parent = ferm[end].matrix[end].parent;
		if (ferm[end].matrix[parent].pass == TMP_CLOSE)
			ferm[parent].matrix[end].pass = TMP_CLOSE;
		else
		{
			ferm[end].matrix[parent].pass = TMP_OPEN;
			ferm[parent].matrix[end].pass = TMP_CLOSE;
		}
		if (ferm[parent].matrix[parent].type != START && ferm[parent].matrix[parent].type != END)
			ferm[parent].matrix[parent].split = 1;
		end = parent;
	}
	return (1);
}

int	mark_rooms(s_ferm *ferm, int branch, int room, s_set_path **stack)
{
	int parent;

	parent = ferm[branch].matrix[branch].parent;
	if (ferm[parent].matrix[parent].split == 0 && ferm[branch].matrix[branch].split > 0)
	{
		if (ferm[room].matrix[room].split == 0)
			return (1);
	}
	push(stack, room);
	ferm[room].matrix[room].parent = branch;
	ferm[room].matrix[room].visit = 1;
	if (ferm[room].matrix[room].type == END)
	{
		while(*stack)
			delete(stack);
		return (END);
	}
	return (1);
}

int	bfs(s_info *info, s_ferm *ferm, int branch)
{
	int room;
	int c_room;
	s_set_path *stack;
	s_set_path *links;

	stack = NULL;
	room = 0;
	c_room = info->c_rooms;
	push(&stack, branch);
	while (stack)
	{
		branch = stack->var;
		links = ferm[branch].links;
		delete(&stack);
		while (links)
		{
			room = links->var;
			if (ferm[branch].matrix[room].pass < CLOSE)
			{
				if(ferm[room].matrix[room].visit == 0)
				{
					if ((mark_rooms(ferm, branch, room, &stack)) == END)
						return (mark_the_path(ferm, room));
				}
			}
			links = links->next;
		}
		room = 0;
	}
	return (0);
}

int search_paths(s_info *info, s_ferm *ferm, int c_paths, int start)
{
	int i;

	i = 0;
	while (i < c_paths)
	{
		if (bfs(info, ferm, start) == 0)
			return (0);
		update_ferm(ferm, info);
		i++;
	}
	return (1);
}