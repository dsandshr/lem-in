/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ferm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:50:23 by tlorine           #+#    #+#             */
/*   Updated: 2019/11/10 14:28:25 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_num(int num, s_set_path **set, s_set_path **s_set)
{
	if (*set == NULL)
	{
		*set = (s_set_path *)malloc(sizeof(s_set_path));
		(*set)->var = num;
		(*set)->next = NULL;
		*s_set = *set;
	}
	else
	{
		(*set)->next = (s_set_path *)malloc(sizeof(s_set_path));
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
	while (tmp)
	{
		add_num(tmp->var, &paths->set, &paths->s_set);
		i++;
		tmp->next;
	}
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
	len = paths->len;
	while (branch < info->c_rooms)
	{
		if(ferm[branch][room].pass == OPEN)
		{
			if (path == 0)
				paths->len++;
			if (path != 0)
			{
				paths->len++;
				len = paths;
				add_num(room, &paths->set, &paths->s_set);
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = add_path(paths);
				tmp = tmp->next;
			}
			create_paths(ferm, info, branch, tmp);
			path++;
		}
		room++;
	}
	if (path == 0)
		paths->go = CLOSE;
}

s_paths	*search_paths(s_ferm **ferm, s_info *info)
{
	int branch;
	s_paths *paths;

	branch = 0;
	paths = (s_paths *)malloc(sizeof(s_paths));
	paths->next = NULL;
	paths->len = 0;
	paths->go = OPEN;
	while (ferm[branch][branch].type != START)
		branch++;
	create_paths(ferm, info, branch, paths);
	return (paths);
}