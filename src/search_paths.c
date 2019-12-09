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
		if (ferm[parent].matrix[end].pass != TMP_OPEN)
			ferm[end].matrix[parent].pass = TMP_OPEN;
		else
			ferm[parent].matrix[end].pass = TMP_CLOSE;
		ferm[parent].matrix[end].pass = TMP_CLOSE;
		if (ferm[parent].matrix[parent].type != START && ferm[parent].matrix[parent].type != END)
			ferm[parent].matrix[parent].split = 1;
		end = parent;
	}
	return (1);
}

int split_vertex(s_set_path *links, s_ferm *ferm, int branch)
{
	while (links)
	{
		if (ferm[branch].matrix[links->var].pass == OPEN && ferm[links->var].matrix[links->var].split == 1)
		{
			if (links->var != branch)
				return (1);
		}
		if (ferm[links->var].matrix[branch].pass == TMP_OPEN || ferm[branch].matrix[links->var].pass == TMP_OPEN)
		{
			if (links->var != branch)
				return (1);
		}
		links = links->next;
	}
	return (0);
}

int	mark_rooms(s_ferm *ferm, int branch, int room, s_set_path **stack)
{
	int parent;

	parent = ferm[branch].matrix[branch].parent;
	// ft_putstr(ferm[room].matrix[branch].name);
	// ft_putchar('-');
	// ft_putendl(ferm[room].matrix[room].name);
	// if ((ft_strcmp("Xyt6", ferm[branch].matrix[branch].name)) == 0)
	// {
	// 	s_set_path *links;

	// 	links = ferm[branch].links;
	// 	ft_putstr (ferm[parent].matrix[parent].name);
	// 	ft_putstr("->");
	// 	ft_putstr (ferm[branch].matrix[branch].name);
	// 	ft_putstr("->");
	// 	ft_putstr (ferm[room].matrix[room].name);
	// 	ft_putstr("\t");
	// 	ft_putnbr(ferm[branch].matrix[branch].split);
	// 	ft_putendl("\n-----------------");
	// 	while (links)
	// 	{
	// 		write(1, "\n", 1);
	// 		ft_putstr (ferm[links->var].matrix[links->var].name);
	// 		ft_putstr("          pass: ");
	// 		if(ferm[branch].matrix[links->var].pass == TMP_CLOSE)
	// 			ft_putstr("TMP_CLOSE");
	// 		if(ferm[branch].matrix[links->var].pass == TMP_OPEN)
	// 			ft_putstr("TMP_OPEN");
	// 		if(ferm[branch].matrix[links->var].pass == OPEN)
	// 			ft_putstr("OPEN");
	// 		ft_putstr("          split: ");
	// 		ft_putnbr(ferm[links->var].matrix[links->var].split);
	// 		links = links->next;
	// 		write(1, "\n", 1);
	// 	}
	// 	ft_putendl("\n-----------------");
	// }
	ferm[room].matrix[room].visit = 1;
	if (ferm[parent].matrix[parent].split == 0 && ferm[branch].matrix[branch].split == 1)
	{
		if (ferm[room].matrix[room].split == 0 && (split_vertex(ferm[branch].links, ferm, branch)) == 1)
			return(1);
	}
	push(stack, room);
	ferm[room].matrix[room].parent = branch;
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
	ferm[branch].matrix[branch].visit = 1;
	push(&stack, branch);
	while (stack)
	{
		branch = stack->var;
		links = ferm[branch].links;
		delete(&stack);
		while (links)
		{
			room = links->var;
			if ((ferm[branch].matrix[room].pass == TMP_OPEN || ferm[branch].matrix[room].pass == OPEN) && room != branch)
			{
				if(ferm[room].matrix[room].visit == 0 && ferm[room].matrix[room].type != START)
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
		{
			update_ferm(ferm, info);
			return (0);
		}
		update_ferm(ferm, info);
		i++;
	}
	return (1);
}