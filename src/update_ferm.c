/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ferm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:50:23 by tlorine           #+#    #+#             */
/*   Updated: 2019/11/17 19:34:58 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

s_paths *add_path(s_paths *parent, int len)
{
	int i;

	i = 0;
	s_paths *path;
	s_set_path *tmp;

	tmp = parent->s_set;
	path = (s_paths *)malloc(sizeof(s_paths));
	path->s_set = NULL;
	path->set = NULL;
	while (i < len)
	{
		add_num(tmp->var, &path->set, &path->s_set);
		i++;
		tmp = tmp->next;
	}
	path->len = len;
	path->go = CLOSE;
	path->next = NULL;
	return (path);
}

int fixation(s_set_path *set, int num, int len)
{
	int i;

	i = 0;
	while (set && i < len)
	{
		if (set->var == num)
			return (1);
		set = set->next;
		len++;
	}
	return (0);
}

void	create_paths(s_ferm **ferm, s_info *info, int branch, s_paths *paths)
{
	int path;
	int len;
	int room;
	s_paths *tmp;

	tmp = paths;
	path = 0;
	room = 0;
	//add_num(branch, &(paths->set), &(paths->s_set));
	paths->len++;
	if (ferm[branch][branch].type == END)
	{
		info->c_path++;
		paths->go = OPEN;
		return ;
	}
	len = paths->len;
	while (room < info->c_rooms)
	{
		if(ferm[branch][room].pass == OPEN && ferm[branch][room].type != START && ferm[room][room].path_lenght != -1)
		{
				// if (path > 0)
				// {
				// 	while (tmp->next != NULL)
				// 		tmp = tmp->next;
				// 	tmp->next = add_path(paths, len);
				// 	tmp = tmp->next;
				// }
				ferm[room][room].path_lenght = -1;
				create_paths(ferm, info, room, tmp);
				ferm[room][room].path_lenght = 1;
				// path++;
		}
		room++;
	}
}

s_paths	*search_paths(s_ferm **ferm, s_info *info)
{
	int branch;
	int rooms;
	s_paths *paths;

	branch = 0;
	rooms = 0;
	paths = (s_paths *)malloc(sizeof(s_paths));
	paths->next = NULL;
	paths->s_set = NULL;
	paths->set = NULL;
	paths->len = 0;
	paths->go = CLOSE;;
	while (ferm[branch][branch].type != START)
		branch++;
	while (rooms < info->c_rooms)
	{
		if(ferm[branch][rooms].pass == OPEN)
			ferm[rooms][branch].pass = CLOSE;
		rooms++;
	}
	create_paths(ferm, info, branch, paths);
	return (paths);
}