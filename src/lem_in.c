/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:20:07 by tlorine           #+#    #+#             */
/*   Updated: 2019/12/15 17:12:42 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		write_map(t_map **map)
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

static void	std_lem_in_work(t_info *inf, t_ferm *frm, t_paths *pth, t_map *map)
{
	pth = find_way(inf, frm);
	if (pth == NULL)
		error_processing(NULL_PATHS_E, &inf);
	write_map(&map);
	march(pth, frm, inf, 0);
	delete_paths(&pth);
}

int			main(int argc, char **argv)
{
	t_info	*info;
	t_ferm	*ferm;
	t_paths *paths;
	t_map	*map;
	short	flg;

	if ((flg = argc) > 1)
		flg = check_flags(argv);
	map = (t_map *)malloc(sizeof(t_map));
	info = read_file(map, 0);
	ferm = create_matrix(info);
	if (argc > 1 && (paths = NULL) == NULL)
		do_flags(flg, info, ferm, paths);
	if (flg == WRITE_STD_PATH)
		writeStdPath(argv[1], ferm, info);
	if (argc == 1)
		std_lem_in_work(info, ferm, paths, map);
	ferm = delete_ferm(ferm, info->c_rooms);
	delete_info(&info);
	return (0);
}
