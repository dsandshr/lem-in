/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:53:59 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/15 19:52:52 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		mark_links(t_ferm *ferm, t_info *info, int room, int branch)
{
	if (room < info->c_rooms)
	{
		push(&ferm[branch].links, room);
		push(&ferm[room].links, branch);
		ferm[branch].matrix[room].pass = OPEN;
		ferm[room].matrix[branch].pass = OPEN;
	}
}

void		search_links(t_info *info, t_ferm *ferm, t_links *links)
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

void		links_add(t_info *info, t_ferm *ferm)
{
	t_links	*links;

	links = info->links;
	while (links != NULL)
	{
		search_links(info, ferm, links);
		links = links->next;
	}
}

void		create_branch(t_info *info, t_matrix *branch)
{
	int		i;
	t_rooms	*all_tunnel;

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

t_ferm		*create_matrix(t_info *info)
{
	t_ferm	*ferm;
	t_rooms	*rooms;

	rooms = info->rooms;
	int		i;

	i = 0;
	ferm = (t_ferm *)malloc(sizeof(t_ferm) * (info->c_rooms));
	while (i < info->c_rooms)
	{
		ferm[i].matrix = (t_matrix *)malloc(sizeof(t_matrix) * (info->c_rooms));
		ferm[i].links = NULL;
		ferm[i].x = rooms->x;
		ferm[i].y = rooms->y;
		create_branch(info, ferm[i].matrix);
		i = i + 1;
		rooms = rooms->next;
	}
	links_add(info, ferm);
	return (ferm);
}
