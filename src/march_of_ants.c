#include "lem_in.h"

void build_paths(s_set_path *set, s_ferm **ferm)
{
	while (set->next)
		set = set->next;
	while (set->back)
	{
		ferm[set->var][set->back->var].pass = OPEN;
		set = set->back;
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
			while (room < info->c_rooms)
			{
				if (ferm[path][room].pass == OPEN)
				{
					push(&stack, room);
					if (ferm[room][room].ants != 0)
					{
						ferm[room][room].ants--;
						ferm[path][path].ants++;
						ferm[path][path].visit = ferm[room][room].visit;
						ft_putstr(" L");
						ft_putnbr(ferm[room][room].visit);
						ft_putchar('-');
						ft_putstr(ferm[path][path].name);
						if (ferm[room][room].type == START)
							ferm[room][room].visit++;
					}
				}
				room++;
			}
			room = 0;
		}
		ft_putchar('\n');
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
			else
			{
				ferm[i][i].ants = 0;
				ferm[i][i].visit = 0;
			}
			ferm[i][rooms].pass = CLOSE;
			rooms++;
		}
		rooms = 0;
		i++;
	}
	i = 0;
	remove_intersections(paths, ferm, END);
	the_walking_line(ferm, info, end);
}