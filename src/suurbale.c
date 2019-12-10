#include "lem_in.h"

void	restore_ferm(s_ferm *ferm, s_info *info)
{
	int branch;
	int room;
	s_set_path *links;

	room = 0;
	branch = 0;

	while (branch < info->c_rooms)
	{
		links = ferm[branch].links;
		while(links)
		{
			room = links->var;
			if (ferm[branch].matrix[room].pass == TMP_CLOSE || ferm[branch].matrix[room].pass == TMP_OPEN)
				ferm[branch].matrix[room].pass = OPEN;
			ferm[branch].matrix[room].split = 0;
			ferm[branch].matrix[room].visit = 0;
			ferm[branch].matrix[room].parent = 0;
			links = links->next;
		}
		if (ferm[branch].matrix[branch].pass == TMP_CLOSE || ferm[branch].matrix[branch].pass == TMP_OPEN)
			ferm[branch].matrix[branch].pass = OPEN;
		ferm[branch].matrix[branch].split = 0;
		ferm[branch].matrix[branch].visit = 0;
		ferm[branch].matrix[branch].parent = 0;
		room = 0;
		branch = branch + 1;
	}
}

s_paths *suurbale(s_ferm *ferm, s_info *info, int c_paths)
{
	s_paths *paths;

	paths = NULL;
	if((search_paths(info, ferm, c_paths, info->start_id)) == 0)
	{
		restore_ferm(ferm, info);
		return (paths);
	}
	// write_ferm(ferm, info, 0);
	// exit (1);
	paths = bfs_for_build(info, ferm, info->end_id);
	restore_ferm(ferm, info);
	return (paths);
}