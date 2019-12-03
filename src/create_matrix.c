/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:53:59 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/03 20:50:09 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_tunnel(s_ferm *branch, s_rooms *rooms, s_info *info, int i)
{
	branch[i].type = rooms->type;
	branch[i].name = rooms->name;
	branch[i].pass = CLOSE;
	branch[i].visit = 0;
	branch[i].parent = 0;
	if (branch[i].type == START)
	{
		info->start_id = i;
		branch[i].ants = info->c_ants;
	}
	else
		branch[i].ants = 0;
	if (branch[i].type == END)
		info->end_id = i;
}

s_ferm	*create_branch(s_info *info)
{
	s_rooms	*all_tunnel;
	s_ferm	*branch;
	int		i;

	i = 0;
	all_tunnel = info->rooms;
	branch = (s_ferm *)malloc(sizeof(s_ferm) * info->c_rooms);
	while (all_tunnel)
	{
		create_tunnel(branch, all_tunnel, info, i);
		all_tunnel = all_tunnel->next;
		i = i + 1;
	}
	return (branch);
}

void	links_add(s_info *info, s_ferm **ferm)
{
	int		branch;
	int		room;
	s_links	*links;

	branch = 0;
	room = 0;
	links = info->links;
	while (links != NULL)
	{
		while (branch < info->c_rooms)
		{
			if (ft_strcmp(ferm[branch][branch].name, links->room1) == 0 || ft_strcmp(ferm[branch][branch].name, links->room2) == 0)
			{
				while (room < info->c_rooms)
				{
					if (room != branch)
					{
						if (ft_strcmp(ferm[room][room].name, links->room1) == 0 || ft_strcmp(ferm[room][room].name, links->room2) == 0)
							break ;
					}
					room = room + 1;
				}
				if (room < info->c_rooms)
				{
					ferm[branch][room].pass = OPEN;
					ferm[room][branch].pass = OPEN;
				}
				branch = info->c_rooms;
			}
			branch = branch + 1;
		}
		room = 0;
		branch = 0;
		links = links->next;
	}
}

s_ferm	**create_matrix(s_info *info)
{
	s_ferm	**ferm;
	s_rooms	*rooms;
	int i;

	i = 0;
	ferm = (s_ferm **)malloc(sizeof(s_ferm *) * (info->c_rooms));
	rooms = info->rooms;
	while (i < info->c_rooms)
	{
		ferm[i] = create_branch(info);
		i = i + 1;
		rooms = rooms->next;
	}
	links_add(info, ferm);
	return (ferm);
}