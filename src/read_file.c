/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:27:26 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/11 18:49:48 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		read_ants(int fd, t_map **map)
{
	char	*line;
	int		ants;

	ants = 0;
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		(*map)->map = line;
		(*map)->next = (t_map *)malloc(sizeof(t_map));
		(*map) = (*map)->next;
		if (line != NULL && line[0] != '#')
		{
			if (ft_thisnum(line))
				return (ft_atoi(line));
			return (FORMAT_E);
		}
		else if (ft_strcmp(line, "##start") == 0\
		|| ft_strcmp(line, "##end") == 0)
		{
			ants = line[2] == 's' ? START_1_E : END_1_E;
			return (ants);
		}
		line = NULL;
	}
	return (NO_ANTS_E);
}

t_info	*read_file(t_map *map, int fd)
{
	int		finish;
	t_info	*info;
	t_map	*map_save;

	map_save = map;
	finish = 0;
	if (!(info = (t_info *)malloc(sizeof(t_info))))
		error_processing(MALLOC_E, &info);
	info->rooms = NULL;
	info->links = NULL;
	info->c_rooms = 0;
	info->c_links = 0;
	info->c_path = 0;
	info->c_ants = read_ants(fd, &map);
	if (info->c_ants < 1)
		error_processing(info->c_ants, &info);
	finish = read_main(info, fd, &map, EMPTY_LINE_E);
	if ((finish < 1))
		error_processing(finish, &info);
	map = map_save;
	return (info);
}
