/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/11/12 14:51:01 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	**adj_matrix(int o_ways)
{
	int **adj_mtx;
	int buf;

	buf = o_ways;
	if (!(adj_mtx = (int **)malloc(sizeof(int *) * (o_ways + 1))))
		exit (-1);
	while (buf != 0)
	{
		adj_mtx[buf] = (int *)malloc(sizeof(int) * (o_ways + 1));
		buf--;
	}
	while(buf <= o_ways)
	{
		adj_mtx[buf][buf] = 1;
		buf++;
	}
}

static void	find_o_ways(s_paths *paths, s_info *info, s_paths_mas *paths_mas)
{
	s_paths	*pointer;
	int		l;

	pointer = paths;
	if (!(paths_mas = (s_paths_mas *)malloc(sizeof(s_paths_mas))))
		exit(-1);
	paths_mas->lenShWay = paths->len;
	paths_mas->lenNepWay = paths->len;
	paths_mas->i = 0;
	if (!(paths_mas->mas = (s_paths *)malloc(sizeof(s_paths) * info->c_path)))
		exit(-1);
	while (paths)
	{
		if (paths->go == OPEN)
		{
			paths_mas->mas[paths_mas->i] = *paths;
			paths_mas->lenShWay = paths_mas->lenShWay > paths->len ? paths->len : paths_mas->lenShWay;
			if (paths->next == NULL)
				break;
			paths = paths->next;
			paths_mas->i++;
		}
		if (paths->go == CLOSE)
		{
			if (paths->next == NULL)
				break;
			paths = paths->next;
		}
	}
}

void	find_way(s_paths *paths, s_info *info)
{
	s_paths_mas *paths_mas;
	//int			ant;

	paths_mas = NULL;
	find_o_ways(paths, info, paths_mas);
	paths_mas->adj_mtx = adj_matrix(paths_mas->i);
	//find_Nep_Ways()
	// ant = info->c_ants;
	// deicstra();
	// find_neperesec();
	// while (ant)
	// if (deicstra < find_neperesec())
	// 	deicstra();
	// else
	// 	neperesec();
}