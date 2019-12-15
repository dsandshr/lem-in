/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:20:07 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/15 20:26:20 by tlorine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	write_map(t_map **map)
{
	t_map *tmp;

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
	t_info	*info;
	t_ferm	*ferm;
	t_paths *paths;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	info = read_file(map, 0);
	ferm = create_matrix(info);
	paths = find_way(info, ferm);
	if (paths == NULL)
		error_processing(NULL_PATHS_E, &info);
	//write_map(&map);
	march(paths, ferm, info);
	delete_paths(&paths);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	return (0);
}
