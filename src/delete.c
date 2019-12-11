/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:17:04 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/11 16:29:08 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	delete_rooms(t_rooms *rooms)
{
	if (rooms != NULL)
	{
		delete_rooms(rooms->next);
		ft_strdel(&(rooms->name));
		free(rooms);
		rooms = NULL;
	}
}

void	delete_links(t_links *links)
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

void	delete_info(t_info **info)
{
	delete_rooms((*info)->rooms);
	(*info)->rooms = NULL;
	delete_links((*info)->links);
	(*info)->links = NULL;
	free(*info);
	*info = NULL;
}

t_ferm	*delete_ferm(t_ferm *ferm, int room)
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
