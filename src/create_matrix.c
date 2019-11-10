/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:53:59 by tlorine           #+#    #+#             */
/*   Updated: 2019/11/06 19:46:38 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int search_pass(s_links *links, char *t_name, char *r_name)
{
	if (ft_strcmp(t_name, r_name))
	{
		while (links)
		{
			if (ft_strcmp(links->room1, t_name) == 0 || ft_strcmp(t_name, links->room2) == 0)
			{
				if (ft_strcmp(links->room1, r_name) == 0 || ft_strcmp(links->room2, r_name) == 0)
					return (OPEN);
			}
			links = links->next;
		}
	}
	return (CLOSE);
}
void	create_tunnel(s_ferm *branch, s_rooms *tunnel, s_rooms *rooms, s_info *info)
{
	branch->type = rooms->type;
	branch->name = rooms->name;
	branch->pass = CLOSE; //search_pass(info->links, tunnel->name, rooms->name);
	branch->visited = OPEN;
	if (branch->type == START)
		branch->ants = info->c_ants;
	else
		branch->ants = 0;
}

s_ferm	*create_branch(s_rooms *tunnel, s_info *info)
{
	s_rooms	*all_tunnel;
	s_ferm	*branch;
	int		i;

	i = 0;
	all_tunnel = info->rooms;
	branch = (s_ferm *)malloc(sizeof(s_ferm) * info->c_rooms);
	while (all_tunnel)
	{
		create_tunnel(&branch[i], tunnel, all_tunnel, info);
		all_tunnel = all_tunnel->next;
		i++;
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
						if (ft_strcmp(ferm[branch][room].name, links->room1) == 0 || ft_strcmp(ferm[branch][room].name, links->room2) == 0)
							break ;
					}
					room++;
				}
				ferm[branch][room].pass = OPEN;
				ferm[room][branch].pass = OPEN;
				break ;
			}
			branch++;
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
	rooms = info->rooms;
	ferm = (s_ferm **)malloc(sizeof(s_ferm *) * (info->c_rooms));
	while (rooms)
	{
		ferm[i] = create_branch(rooms, info);
		i++;
		rooms = rooms->next;
	}
	links_add(info, ferm);
	return (ferm);
}