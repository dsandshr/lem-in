#include "lem_in.h"

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
			if (ferm[branch][room].pass == OPEN)
				ferm[branch][room].pass = TMP_CLOSE;
			if (ferm[branch][room].split != 0)
				ferm[branch][room].split = 0;
			room = room + 1;
		}
		branch = branch + 1;
		room = 0;
	}
}


void	remove_intersections(s_paths *paths, s_ferm **ferm)
{
	s_set_path *set;

	while (paths)
	{
		set = paths->s_set;
		while (set->next)
		{
			if (ferm[set->var][set->next->var].pass == TMP_OPEN)
			{
				ferm[set->next->var][set->var].pass = TMP_CLOSE;
				ferm[set->var][set->next->var].pass = TMP_CLOSE;
			}
			else
				ferm[set->next->var][set->var].pass = TMP_OPEN;
			set = set->next;
		}
		paths = paths->next;
	}
}

void	restore_ferm(s_ferm **ferm, s_info *info)
{
	int branch;
	int room;

	room = 0;
	branch = 0;

	while (branch < info->c_rooms)
	{
		while(room < info->c_rooms)
		{
			if (ferm[branch][room].pass == TMP_CLOSE || ferm[branch][room].pass == TMP_OPEN)
				ferm[branch][room].pass = OPEN;
			ferm[branch][room].split = 0;
			ferm[branch][room].visit = 0;
			ferm[branch][room].parent = 0;
			room = room + 1;
		}
		room = 0;
		branch = branch + 1;
	}
}

s_paths *suurbale(s_ferm **ferm, s_info *info, int c_paths)
{
	s_paths *paths;

	if((paths = search_paths(info, ferm, c_paths, info->start_id)) == NULL)
	{
		restore_ferm(ferm, info);
		return (NULL);
	}
	// close_pass(ferm, info);
	remove_intersections(paths, ferm);
	delete_paths(&paths);
	paths = bfs_for_build(info, ferm, info->start_id);
	restore_ferm(ferm, info);
	return (paths);
}