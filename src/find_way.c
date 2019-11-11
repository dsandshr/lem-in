/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/11/11 15:35:59 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	find_o_ways(s_paths *paths, s_info *info, s_paths_mas *paths_mas)
{
	s_paths	*pointer;

	pointer = paths;
	if (!(paths_mas = (s_paths_mas *)malloc(sizeof(s_paths_mas))))
		exit(-1);
	paths_mas->i = 0;
	if (!(paths_mas->mas = (s_paths *)malloc(sizeof(s_paths ) * info->c_path + 1)))
		exit(-1);
	while (paths)
	{
		if (paths->go == OPEN)
		{
			paths_mas->mas[paths_mas->i] = *paths;
			paths = paths->next;
			paths_mas->i++;
		}
		if (paths->go == CLOSE)
			paths = paths->next;
	}
	paths_mas->i = 0;
	while (paths_mas->i <= info->c_path)
	{
		if (paths_mas->mas[paths_mas->i].go == OPEN)
			write(1, "1", 1);
		else if (paths_mas->mas[paths_mas->i].go == CLOSE)
			write (1, "0", 1);
		paths_mas->i++;
	}
}

void	find_way(s_paths *paths, s_info *info)
{
	s_paths_mas *paths_mas;
	//int			ant;

	paths_mas = NULL;
	find_o_ways(paths, info, paths_mas);
	// ant = info->c_ants;
	// deicstra();
	// find_neperesec();
	// while (ant)
	// if (deicstra < find_neperesec())
	// 	deicstra();
	// else
	// 	neperesec();
}