/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:53:59 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/10 20:06:06 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		mark_links(s_ferm *ferm, s_info *info, int room, int branch)
{
	if (room < info->c_rooms)
	{
		push(&ferm[branch].links, room);
		push(&ferm[room].links, branch);
		ferm[branch].matrix[room].pass = OPEN;
		ferm[room].matrix[branch].pass = OPEN;
	}
}

void		search_links(s_info *info, s_ferm *ferm, s_links *links)
{
	int		branch;
	int		room;

	branch = 0;
	room = 0;
	while (branch < info->c_rooms)
	{
		if (ft_strcmp(ferm[0].matrix[branch].name, links->room1) == 0\
		|| ft_strcmp(ferm[0].matrix[branch].name, links->room2) == 0)
		{
			while (room < info->c_rooms)
			{
				if (room != branch)
				{
					if (ft_strcmp(ferm[0].matrix[room].name, links->room1) == 0\
					|| ft_strcmp(ferm[0].matrix[room].name, links->room2) == 0)
						break ;
				}
				room = room + 1;
			}
			mark_links(ferm, info, room, branch);
			break ;
		}
		branch++;
	}
}

void		links_add(s_info *info, s_ferm *ferm)
{
	s_links	*links;

	links = info->links;
	while (links != NULL)
	{
		search_links(info, ferm, links);
		links = links->next;
	}
}

void		create_branch(s_info *info, s_matrix *branch)
{
	int		i;
	s_rooms	*all_tunnel;

	i = 0;
	all_tunnel = info->rooms;
	while (i < info->c_rooms)
	{
		branch[i].type = all_tunnel->type;
		branch[i].name = all_tunnel->name;
		branch[i].pass = CLOSE;
		branch[i].visit = 0;
		branch[i].parent = 0;
		branch[i].split = 0;
		branch[i].ants = 0;
		if (branch[i].type == START)
			info->start_id = i;
		if (branch[i].type == START)
			branch[i].ants = info->c_ants;
		else
			branch[i].ants = 0;
		if (branch[i].type == END)
			info->end_id = i;
		all_tunnel = all_tunnel->next;
		i++;
	}
}

s_ferm		*create_matrix(s_info *info)
{
	s_ferm	*ferm;
	int		i;

	i = 0;
	ferm = (s_ferm *)malloc(sizeof(s_ferm) * (info->c_rooms));
	while (i < info->c_rooms)
	{
		ferm[i].matrix = (s_matrix *)malloc(sizeof(s_matrix) * (info->c_rooms));
		ferm[i].links = NULL;
		create_branch(info, ferm[i].matrix);
		i = i + 1;
	}
	links_add(info, ferm);
	return (ferm);
}
