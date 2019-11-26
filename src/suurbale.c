#include "lem_in.h"

s_ferm **copy_ferm(s_ferm **ferm, s_info *info)
{
	int branch;
	int room;
	s_ferm **clone;

	branch = 0;
	room = 0;
	clone = (s_ferm **)malloc(sizeof(s_ferm *) * info->c_rooms);
	while (branch < info->c_rooms)
	{
		clone[branch] = (s_ferm *)malloc(sizeof(s_ferm) * info->c_rooms);
		while (room < info->c_rooms)
		{
			clone[branch][room].name = ferm[branch][room].name;
			clone[branch][room].ants = ferm[branch][room].ants;
			clone[branch][room].pass = ferm[branch][room].pass;
			clone[branch][room].parent = ferm[branch][room].parent;
			clone[branch][room].type = ferm[branch][room].type;
			clone[branch][room].visit = ferm[branch][room].visit;
			clone[branch][room].split = ferm[branch][room].split;
			room++;
		}
		room = 0;
		branch++;
	}
	return (clone);
}

void	close_pass(s_ferm **ferm, s_info *info)
{
	int branch;
	int room;

	branch = 0;
	room = 0;
	while (branch < info->c_rooms)
	{
		while (room < info->c_rooms)
		{
			ferm[branch][room].pass = CLOSE;
			room++;
		}
		branch++;
		room = 0;
	}
}


void	remove_intersections(s_paths *paths, s_ferm **ferm, int flag)
{
	s_set_path *set;

	while (paths)
	{
		set = paths->s_set;
		while (set->next)
		{
			if (flag == END)
				ferm[set->var][set->next->var].pass = OPEN;
			else if (ferm[set->var][set->next->var].pass == OPEN)
				ferm[set->var][set->next->var].pass = CLOSE;
			else
				ferm[set->next->var][set->var].pass = OPEN;
			set = set->next;
		}
		paths = paths->next;
	}
}

s_paths *suurbale(s_ferm **ferm, s_info *info, int c_paths)
{
	s_paths *paths;
	s_ferm **ferm_clone;

	ferm_clone = copy_ferm(ferm, info);
	if((paths = search_paths(info, ferm_clone, c_paths)) == NULL)
	{
		ferm_clone = delete_ferm(ferm_clone, info->c_rooms);
		return (NULL);
	}
	close_pass(ferm_clone, info);
	remove_intersections(paths, ferm_clone, START);
	delete_paths(&paths);
	paths = search_paths(info, ferm_clone, c_paths);
	ferm_clone = delete_ferm(ferm_clone, info->c_rooms);
	// write_paths(paths, ferm);
	return (paths);
}