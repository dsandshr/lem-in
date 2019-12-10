/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:17:04 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/10 20:06:07 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	delete_rooms(s_rooms *rooms)
{
	if (rooms != NULL)
	{
		delete_rooms(rooms->next);
		ft_strdel(&(rooms->name));
		free(rooms);
		rooms = NULL;
	}
}

void	delete_links(s_links *links)
{
	if (links != NULL)
	{
		delete_links(links->next);
		ft_strdel(&(links->room1));
		ft_strdel(&(links->room2));
		free(links);
		links = NULL;
	}
}

void	delete_info(s_info **info)
{
	delete_rooms((*info)->rooms);
	(*info)->rooms = NULL;
	delete_links((*info)->links);
	(*info)->links = NULL;
	free(*info);
	*info = NULL;
}

s_ferm	*delete_ferm(s_ferm *ferm, int room)
{
	room = room - 1;
	while (room != -1)
	{
		free(ferm[room].matrix);
		while (ferm[room].links != NULL)
			delete(&(ferm[room].links));
		ferm[room].matrix = NULL;
		room--;
	}
	free(ferm);
	ferm = NULL;
	return (ferm);
}
