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
		branch = branch + 1;
	}
}

int mark_the_path(s_ferm **ferm, int end)
{
	int parent;

	while (ferm[end][end].type != START)
	{
		parent = ferm[end][end].parent;
		if (ferm[end][parent].pass == TMP_CLOSE)
			ferm[parent][end].pass = TMP_CLOSE;
		else
		{
			ferm[end][parent].pass = TMP_OPEN;
			ferm[parent][end].pass = TMP_CLOSE;
		}
		if (ferm[parent][parent].type != START && ferm[parent][parent].type != END)
			ferm[parent][parent].split = ferm[parent][parent].split + 1;
		end = parent;
	}
	return (1);
}

int	mark_rooms(s_ferm **ferm, int branch, int room, s_set_path **stack)
{
	int parent;

	parent = ferm[branch][branch].parent;
	if (ferm[parent][parent].split == 0 && ferm[branch][branch].split > 0)
	{
		if (ferm[room][room].split == 0)
			return (1);
	}
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

int	bfs(s_info *info, s_ferm **ferm, int start)
{
	int branch;
	int room;
	s_set_path *stack;

	stack = NULL;
	branch = start;
	room = 0;
	push(&stack, branch);
	while (stack)
	{
		branch = stack->var;
		delete(&stack);
		while (room < info->c_rooms && branch < info->c_rooms)
		{
			if ((ferm[branch][room].pass == OPEN ||  ferm[branch][room].pass == TMP_OPEN) && ferm[room][room].visit == 0)
			{
				if ((mark_rooms(ferm, branch, room, &stack)) == END)
					return (mark_the_path(ferm, room));
			}
			room = room + 1;
		}
		room = 0;
	}
	return (0);
}

int search_paths(s_info *info, s_ferm **ferm, int c_paths, int start)
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