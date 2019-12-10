/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:20:07 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/10 20:03:32 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	write_map(s_map **map)
{
	s_map *tmp;

	while (*map != NULL)
	{
		tmp = *map;
		ft_putendl((*map)->map);
		*map = (*map)->next;
		ft_strdel(&tmp->map);
		free(tmp);
		tmp = NULL;
	}
	write(1, "\n", 1);
}

int		main(void)
{
	s_info	*info;
	s_ferm	*ferm;
	s_paths *paths;
	s_map	*map;

	map = (s_map *)malloc(sizeof(s_map));
	info = read_file(map, 0);
	ferm = create_matrix(info);
	paths = find_way(info, ferm);
	if (paths == NULL)
		error_processing(NULL_PATHS_E, &info);
	write_map(&map);
	march(paths, ferm, info);
	delete_paths(&paths);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	return (0);
}
