/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:55:16 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/16 18:13:41 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms			*create_room(char **param, int type, int x, int y)
{
	t_rooms		*rooms;

	rooms = (t_rooms *)malloc(sizeof(t_rooms));
	rooms->name = param[0];
	rooms->x = x;
	rooms->y = y;
	rooms->type = type;
	rooms->next = NULL;
	return (rooms);
}

int				add_rooms(t_info *info, const char *line, int type)
{
	t_rooms	*rooms;
	char	**param;
	int		x;
	int		y;

	rooms = info->rooms;
	param = ft_strsplit(line, ' ');
	x = ft_atoi(param[1]);
	y = ft_atoi(param[2]);
	if (rooms == NULL)
		info->rooms = create_room(param, type, x, y);
	else
	{
		while (rooms->next != NULL)
		{
			if (rooms->x == x && rooms->y == y)
				error_processing(SAME_COORDS_E, &info);
			rooms = rooms->next;
		}
		rooms->next = create_room(param, type, x, y);
	}
	free(param[1]);
	free(param[2]);
	free(param);
	return (1);
}
