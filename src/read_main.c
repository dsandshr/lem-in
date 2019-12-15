/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:56:57 by tlorine           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/12/15 19:53:34 by tlorine          ###   ########.fr       */
=======
/*   Updated: 2019/12/15 17:19:05 by dsandshr         ###   ########.fr       */
>>>>>>> d37f22957a1353a75445a8e52d8d2b2f73933405
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				add_rooms(t_info *info, const char *line, int type)
{
	t_rooms	*rooms;
	char	**param;

	rooms = info->rooms;
	param = ft_strsplit(line, ' ');
	if (rooms == NULL)
	{
		info->rooms = (t_rooms *)malloc(sizeof(t_rooms));
		info->rooms->name = param[0];
		info->rooms->x = ft_atoi(param[1]);
		info->rooms->y = ft_atoi(param[2]);
		info->rooms->type = type;
		info->rooms->next = NULL;
	}
	else
	{
		while (rooms->next != NULL)
			rooms = rooms->next;
		rooms->next = (t_rooms *)malloc(sizeof(t_rooms));
		rooms->next->name = param[0];
		rooms->next->x = ft_atoi(param[1]);
		rooms->next->y = ft_atoi(param[2]);
		rooms->next->type = type;
		rooms->next->next = NULL;
	}
	free(param[1]);
	free(param[2]);
	free(param);
	return (1);
}

int				add_links(t_info *info, const char *line)
{
	t_links	*links;
	char	**param;

	links = info->links;
	param = ft_strsplit(line, '-');
	if (links == NULL)
	{
		info->links = (t_links *)malloc(sizeof(t_links));
		info->links->room1 = param[0];
		info->links->room2 = param[1];
		info->links->next = NULL;
	}
	else
	{
		while (links->next)
			links = links->next;
		links->next = (t_links *)malloc(sizeof(t_links));
		links->next->room1 = param[0];
		links->next->room2 = param[1];
		links->next->next = NULL;
	}
	free(param);
	param = 0;
	return (1);
}

void			comment(t_read_main *srm, char *line)
{
	if (ft_strcmp(line, "##start") == 0)
	{
		srm->type = START;
		srm->start += 1;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		srm->type = END;
		srm->end += 1;
	}
}

int				room_or_links(t_read_main *srm, t_info *info, char *line)
{
	int		num;

	num = 1;
	if (line[0] == '\0')
		error_processing(EMPTY_LINE_E, &info);
	else if (line[0] == '#')
		comment(srm, line);
	else
	{
		num = valid_format(line, info);
		if (num == 1)
			info->c_rooms += add_rooms(info, line, srm->type);
		else if (num == 2)
			info->c_links += add_links(info, line);
		srm->type = TUNNEL;
	}
	return (num);
}

int				read_main(t_info *info, int fd, t_map **map, int num)
{
	t_read_main	srm;
	t_map		*tmp;

	srm.type = TUNNEL;
	srm.start = 0;
	srm.end = 0;
	num = EMPTY_LINE_E;
	(*map)->map = NULL;
	while (get_next_line(fd, &(*map)->map))
	{
		num = room_or_links(&srm, info, (*map)->map);
		tmp = *map;
		(*map)->next = (t_map *)malloc(sizeof(t_map));
		*map = (*map)->next;
		(*map)->map = NULL;
		if (srm.start > 1 || srm.end > 1)
			error_processing(srm.start > 1 ? START_2_E : END_2_E, &info);
		if (num < 1)
			break ;
	}
	free(*map);
	tmp->next = NULL;
	if (srm.start < 1 || srm.end < 1)
		error_processing(srm.start < 1 ? NO_START : NO_END, &info);
	return (num > 0 ? 1 : num);
}
