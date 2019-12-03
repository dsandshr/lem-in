#include "lem_in.h"

void b_paths(s_paths *set, s_ferm **ferm)
{
	s_set_path *mn;

	int tmp_i;

	tmp_i = 0;
	while (set)
	{
		mn = set->set;
		while (mn->back)
		{
			ferm[mn->var][mn->back->var].pass = OPEN;
			ferm[mn->var][mn->var].split = set->go;
			mn = mn->back;
		}
		set = set->next;
		tmp_i++;
	}
}

void step(s_ferm **ferm, s_set_path **stack, int path, int room)
{
	if (ferm[path][room].pass == OPEN)
	{
		push(stack, room);
		if (ferm[room][room].ants != 0)
		{
			ferm[path][path].split--;
			ferm[room][room].ants--;
			ferm[path][path].ants++;
			ferm[path][path].visit = ferm[room][room].visit;
			write(1, "L", 1);
			ft_putnbr(ferm[room][room].visit);
			write(1, "-", 1);
			ft_putstr(ferm[path][path].name);
			write(1, " ", 1);
			if (ferm[room][room].type == START)
				ferm[room][room].visit++;
		}
	}
}

void the_walking_line(s_ferm **ferm, s_info *info, int end)
{
	int room;
	int path;
	s_set_path *stack;

	stack = NULL;
	path = 0;
	room = 0;
	while (ferm[end][end].ants < info->c_ants)
	{
		push(&stack, end);
		while(stack)
		{
			path = stack->var;
			delete(&stack);
			while (room < info->c_rooms && (ferm[path][path].split > 0 || ferm[path][path].type == END))
			{
				step(ferm, &stack, path, room);
				room++;
			}
			room = 0;
		}
		write(1, "\n", 1);
	}

}

void march(s_paths *paths, s_ferm **ferm, s_info *info)
{
	int i;
	int start;
	int end;
	int rooms;

	i = 0;
	rooms = 0;
	while (i < info->c_rooms)
	{
		while (rooms < info->c_rooms)
		{
			if (ferm[i][i].type == START)
			{
				ferm[i][i].ants = info->c_ants;
				ferm[i][i].visit = 1;
				start = i;
			}
			else if (ferm[i][i].type == END)
				end = i;
			ferm[i][rooms].pass = CLOSE;
			ferm[i][rooms].split = 0;
			rooms++;
		}
		rooms = 0;
		i++;
	}
	b_paths(paths, ferm);
	the_walking_line(ferm, info, end);
}