/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 20:20:52 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/10 16:30:48 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			room_exists(const char *line, s_info *info, char end)
{
	s_rooms	*room;
	int		i;

	i = 0;
	room = info->rooms;
	while (room != NULL)
	{
		while (line[i] != end && room->name[i] != '\0')
		{
			if (line[i] != room->name[i])
				break ;
			i++;
		}
		if (line[i] == end && room->name[i] == '\0')
			return (1);
		i = 0;
		room = room->next;
	}
	return (0);
}

int			thisroom(const char *line)
{
	int		i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (line[i] != ' ' || line[i + 1] == ' ')
		return (0);
	i++;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] != ' ' || line[i + 1] == '\0')
		return (0);
	i++;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	return (line[i] == '\0' ? 1 : 0);
}

int			thislink(const char *line)
{
	int		i;

	i = 0;
	while (line[i] != '-' && line[i] != '\0' && line[i] > 32)
		i++;
	if (line[i] != '-')
		return (0);
	i++;
	while (line[i] != '-' && line[i] != '\0' && line[i] > 32)
		i++;
	return (line[i] == '\0' ? 1 : 0);
}

int			valid_format(const char *line, s_info *info)
{
	int		room;
	int		link;

	room = thisroom(line);
	link = thislink(line);
	if (room)
	{
		if (line[0] == 'L')
			return (NEW_L_E);
		return ((room_exists(line, info, ' ')) == 1 ? ROOM_EXIST_E : 1);
	}
	else if (link)
	{
		if ((room_exists(line, info, '-')) == 0)
			return (NO_ROOM_E);
		while (line[room] != '-' && line[room] != '\0')
			room++;
		if ((room_exists(line + (room + 1), info, '\0')) == 0)
			return (NO_ROOM_E);
		return (2);
	}
	else
		return (FORMAT_E);
}
