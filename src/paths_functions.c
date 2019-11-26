#include "lem_in.h"

void	delete_paths(s_paths **path)
{
	s_set_path *tmp_set;
	s_paths *tmp_paths;

	tmp_set = (*path)->s_set;
	while ((*path))
	{
		tmp_paths = *path;
		while ((*path)->s_set)
		{
			tmp_set = (*path)->s_set;
			(*path)->s_set = (*path)->s_set->next;
			free(tmp_set);
			tmp_set = NULL;
		}
		(*path) = (*path)->next;
		free(tmp_paths);
		tmp_paths = NULL;
	}
}

void	add_num(int num, s_set_path **set, s_set_path **s_set)
{
	if (*set == NULL)
	{
		*set = (s_set_path *)malloc(sizeof(s_set_path));
		(*set)->var = num;
		(*set)->next = NULL;
		(*set)->back = NULL;
		*s_set = *set;
	}
	else
	{
		(*set)->next = (s_set_path *)malloc(sizeof(s_set_path));
		(*set)->next->back = *set;
		*set = (*set)->next;
		(*set)->var = num;
		(*set)->next = NULL;
	}
}