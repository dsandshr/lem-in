/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:46:06 by dsandshr          #+#    #+#             */
/*   Updated: 2019/11/11 14:24:37 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	*find_o_ways(s_paths *paths, s_info *info, s_paths_mas *paths_mas)
{
	
}

void	find_way(s_paths *paths, s_info *info)
{
	s_paths_mas *paths_mas;
	int			ant;

	find_o_ways(paths, info, paths_mas);
	ant = info->c_ants;
	deicstra();
	find_neperesec();
	while (ant)
	if (deicstra < find_neperesec())
		deicstra();
	else
		neperesec();