/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ferm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:50:23 by tlorine           #+#    #+#             */
/*   Updated: 2019/11/10 12:17:57 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

s_set_path *add_num(int num, s_paths *path, int flag)
{
	s_set_path *tmp;

	if ((flag == 0 && path->s_nodes == NULL) || (flag == 1 && path->s_set == NULL))
	{
		tmp = (s_set_path *)malloc(sizeof(s_set_path));
		tmp->var = num;
		if (flag == 0)
			path->s_nodes = tmp;
		else
			path->s_set = tmp;
		return (tmp);
	}
	tmp = (s_set_path *)malloc(sizeof(s_set_path));
	tmp->var = num;
	return (tmp);
}

s_paths *add_path(s_paths *parent)
{
	s_paths *path;

	path = (s_paths *)malloc(sizeof(s_paths));
	path->len = parent->len;
	path->next = NULL;
	return (path);
}

void	create_paths(s_ferm **ferm, s_info *info, int branch, s_paths *paths)
{
	int path;
	int len;
	int room;

	path = 0;
	room = 0;
	len = paths->len;
	paths->set = add_num(branch);
	while (branch < info->c_rooms)
	{
		if(ferm[branch][room].pass == OPEN)
		{
			paths->len++;
			if (path != 0)
			{
				paths->nodes = add_num(room);
				paths->next = add_path(paths);
				paths = paths->next;
			}
			create_paths(ferm, info, branch, paths);
			path++;
		}
		room++;
	}
	if (path == 0)
		ferm[branch][branch].pass = CLOSE;
}

s_paths	*search_paths(s_ferm **ferm, s_info *info)
{
	int branch;
	s_paths *paths;

	branch = 0;
	paths = (s_paths *)malloc(sizeof(s_paths));
	paths->next = NULL;
	paths->len = 0;
	while (ferm[branch][branch].type != START)
		branch++;
	paths->s_nodes = paths->nodes;
	paths->s_set = paths->set;
	create_paths(ferm, info, branch, paths);
	return (paths);
}